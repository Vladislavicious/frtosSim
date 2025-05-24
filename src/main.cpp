#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#include "common.h"
#include "time_sv.h"
#include "logger.h"
#include "loggable.h"

class FakeLogger : public Loggable
{
public:
};

static const std::string loggerDataPath = std::string( TEST_DATA_DIR ) + std::string( "/logger/" );

FakeLogger GetLogger( std::string path )
{
  LoggerConfig appConfig;
  ConfigError result = appConfig.ParseConfig( loggerDataPath + std::string( "fakeSim/" ) + path );
  LoggerInterface* appLogInterface = LoggerFabric::GetLogger( appConfig );
  FakeLogger newLoggable;
  newLoggable.SetLogger( appLogInterface );

  return newLoggable;
}
void del( long int ms )
{
  std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
}

FakeLogger appLoggable = GetLogger( "mainApp.json" );

struct HexCharStruct
{
  unsigned char c;
  HexCharStruct( unsigned char _c ) : c( _c ) {}
};

inline std::ostream& operator<<( std::ostream& o, const HexCharStruct& hs )
{
  return ( o << " 0x" << std::hex << ( int )hs.c );
}

inline HexCharStruct hex( unsigned char _c )
{
  return HexCharStruct( _c );
}

std::atomic<bool> stop_output( false );
std::atomic<bool> pause_output( false ); // Флаг для остановки вывода
std::atomic<int> speed_ms( 1 );
// Выводит список доступных команд
void printHelp() {
  std::cout << "\nAvailable commands:\n";
  std::cout << "c - Continue execution\n";
  std::cout << "s - Change speed (current: " << speed_ms << ")\n";
  std::cout << "t - Show statistics\n";
  std::cout << "p - Stop execution\n";
  std::cout << "Enter command: ";
}

// Обработчик ввода пользователя
void inputHandler() {
  std::string input;
  while( !stop_output ) {
    std::getline( std::cin, input );  // Ждём ввода
    if( !pause_output )
    {
      appLoggable.Log( "execution paused\n" );
      pause_output = true;
    }

    if( input.empty() ) {
      printHelp();
      continue;
    }

    char cmd = input[0];
    switch( cmd ) {
    case 'c': // Продолжить выполнение
      pause_output = false;
      std::cout << "Resuming...\n";
      break;

    case 's': // Изменить скорость
    {
      std::cout << "Enter new speed: ";
      int new_speed;
      if( std::cin >> new_speed && new_speed > 0 ) {
        speed_ms = new_speed;

        std::cout << "Speed set to " << speed_ms << "\n";
        appLoggable.Log( LogLevel::INFO, "Speed change applied" );
        appLoggable.SetTimestamps( false );
        appLoggable.Log( "\n" );
        appLoggable.SetTimestamps( true );

      }
      else {
        std::cout << "Invalid speed value!\n";
      }
      std::cin.ignore(); // Очистка буфера после ввода числа
    }
    break;

    case 'p': // Прервать выполнение
      stop_output = true;
      appLoggable.Log( LogLevel::INFO, "Saving simulators state\n\n" );
      del( 5 );
      appLoggable.Log( LogLevel::INFO, "EXIT - OK\n" );

      break;

    default:
      std::cout << "Unknown command.\n";
      break;
    }
  }
}
// Функция для постоянного вывода строк
void continuousOutput() {
  ApplicationGlobalInfo::Instance().SetInitialTimeDelta( TimeSV::Now() );

  FakeLogger sim1tx = GetLogger( "sim1.json" );
  FakeLogger sim2tx = GetLogger( "sim2.json" );

  appLoggable.Log( "start loading configs\n\n" );
  del( 2 );
  appLoggable.Log( LogLevel::INFO, "CONFIG - OK\n" );
  appLoggable.Log( "start build tasks\n\n" );
  del( 700 );
  appLoggable.Log( LogLevel::INFO, "BUILD - OK\n\n" );
  del( 10 );
  appLoggable.Log( "start simulation \n\n" );

  appLoggable.Log( LogLevel::INFO, "sim1 started\n" );
  del( 1 );
  sim1tx.Log( "peripheral initialization\n\n" );
  sim1tx.Log( LogLevel::WARNING, "Bad clock init\n" );
  appLoggable.Log( LogLevel::INFO, "sim2 started\n\n" );
  del( 1 );
  sim2tx.Log( "peripheral initialization\n\n" );


  const int valStrLength = 14;
  char value[valStrLength] = "hello, world!";
  std::stringstream bytesValue;
  for( int i = 0; i < valStrLength; i++ )
  {
    bytesValue << hex( value[i] );
  }

  std::string SendString = "send 10 bytes (uart)\n";
  std::string ReceiveString = "received 10 bytes (uart):\n" + bytesValue.str() + "\n";

  int counter = 0;
  while( !stop_output )
  {
    if( !pause_output )
    {
      if( !pause_output ) {
        sim1tx.Log( LogLevel::INFO, SendString );
        sim2tx.Log( LogLevel::INFO, ReceiveString );
      }

      del( 495 );
      if( !pause_output ) {
        sim1tx.Log( LogLevel::INFO, SendString );
        sim2tx.Log( LogLevel::INFO, ReceiveString );

        sim2tx.Log( LogLevel::INFO, SendString );
        sim1tx.Log( LogLevel::INFO, ReceiveString );

        appLoggable.Log( LogLevel::INFO, "alive: " + std::to_string( counter++ ) + "\n" );
      }
      del( 495 );
    }
    else {
      del( 5 );
    }

  }
}

int main() {
  std::thread outputThread( continuousOutput );
  std::thread inputThread( inputHandler );

  outputThread.join();
  inputThread.join();

  return 0;
}
