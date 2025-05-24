#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <fstream>

#include "logger.h"
#include "loggable.h"
using namespace std;

static const std::string loggerDataPath = std::string( TEST_DATA_DIR ) + std::string( "/logger/" );
//---------------------------------------------------------------
TEST( logger, FileSingleWrite ) {

  LoggerConfig config;
  ConfigError result = config.ParseConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "123456789";
  logger->Output( outString );

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( outString.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
TEST( logger, FileMultiWrite ) {

  LoggerConfig config;
  ConfigError result = config.ParseConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "123456789";
  std::string expectedOutString{ "" };
  for( uint32_t i = 0; i < 5; i++ )
  {
    logger->Output( outString );
    expectedOutString += outString;
  }

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( expectedOutString.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
TEST( logger, FileNullWrite ) {

  LoggerConfig config;
  ConfigError result = config.ParseConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "";
  logger->Output( outString );

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( outString.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
TEST( logger, InfoLevelWrite ) {

  LoggerConfig config;
  ConfigError result = config.ParseConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  logger->SetLogLevel( LogLevel::INFO );

  std::string expectedStr{ "Info: 123" };
  std::string outString = "123";
  logger->Output( outString );

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( expectedStr.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
class FakeLogger : public Loggable
{
};
//---------------------------------------------------------------
TEST( logger, ChangeLoggers ) {

  LoggerConfig fileConfig;
  ConfigError result = fileConfig.ParseConfig( loggerDataPath + std::string( "fileLogNorm.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerConfig consoleConfig;
  result = consoleConfig.ParseConfig( loggerDataPath + std::string( "consoleLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* fileLogger = LoggerFabric::GetLogger( fileConfig );
  EXPECT_TRUE( fileLogger != nullptr );

  FakeLogger loggable;
  loggable.SetLogger( fileLogger );
  loggable.SetTimestamps( true );

  std::string noneOutString = "regular text\n";
  std::string outString = "info level text\n";

  std::string warningOutString = "text on warning level\n";
  std::string errorOutString = "text on error level\n";

  loggable.Log( LogLevel::NONE, noneOutString );
  loggable.Log( LogLevel::INFO, outString );
  loggable.Log( LogLevel::WARNING, warningOutString );
  loggable.Log( LogLevel::ERROR, errorOutString );

  LoggerInterface* consoleLogger = LoggerFabric::GetLogger( consoleConfig );
  EXPECT_TRUE( consoleLogger != nullptr );
  loggable.SetLogger( consoleLogger );

  loggable.Log( LogLevel::NONE, noneOutString );
  loggable.Log( LogLevel::INFO, outString );
  loggable.Log( LogLevel::WARNING, warningOutString );
  loggable.Log( LogLevel::ERROR, errorOutString );
}
//---------------------------------------------------------------
FakeLogger GetLogger( std::string path )
{
  LoggerConfig appConfig;
  ConfigError result = appConfig.ParseConfig( loggerDataPath + std::string( "fakeSim/" ) + path );
  EXPECT_TRUE( result.IsOk() );
  LoggerInterface* appLogInterface = LoggerFabric::GetLogger( appConfig );
  EXPECT_TRUE( appLogInterface != nullptr );
  FakeLogger appLoggable;
  appLoggable.SetLogger( appLogInterface );

  return appLoggable;
}
void del( long int ms )
{
  std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
}

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
//---------------------------------------------------------------
TEST( logger, FakeAppStart ) {
  FakeLogger appLoggable = GetLogger( "mainApp.json" );
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

  for( int i = 0; i < 10; i++ ) {
    sim1tx.Log( LogLevel::INFO, SendString );
    sim2tx.Log( LogLevel::INFO, ReceiveString );

    del( 495 );

    sim2tx.Log( LogLevel::INFO, SendString );
    sim1tx.Log( LogLevel::INFO, ReceiveString );

    appLoggable.Log( LogLevel::INFO, "alive: " + std::to_string( i ) + "\n" );
    del( 495 );
  }
}
//---------------------------------------------------------------
