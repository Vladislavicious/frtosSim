#include "logger.h"
#include <fstream>
#include <iostream>
//---------------------------------------------------------------
// TODO:
// Think of thread-independent solution
class ConsoleLogger : public LoggerInterface
{
public:
  ~ConsoleLogger() override {};

  void Output( const std::string& data ) override {
    SetOutputColor( GetLogLevel() );
    std::cout << data;
  };
private:
  void SetOutputColor( LogLevel level )
  {
    int textColor = 31;
    switch( level ) {
    case LogLevel::INFO:
      textColor = 32;
      break;
    case LogLevel::WARNING:
      textColor = 33;
      break;
    case LogLevel::ERROR:
      textColor = 31;
      break;
    default:
      textColor = 30;
    }
    std::cout << "\033[" << textColor << "m";
  }
};
//---------------------------------------------------------------
class FileLogger : public LoggerInterface
{
public:
  FileLogger( const std::string& fileName ) :
    FileName( fileName ) {
    stream.open( FileName, std::ios::trunc );
    stream.close();
  };
  ~FileLogger() override { stream.close(); };
  void Output( const std::string& data ) override {
    stream.open( FileName, std::ios::app );
    if( stream.is_open() ) {
      stream << GetLevelString() + data;
      // stream << data;
    }
    stream.flush();
    stream.close();
  };
private:
  const std::string GetLevelString() {
    switch( GetLogLevel() )
    {
    case LogLevel::INFO:
      return std::string( "Info: " );
    case LogLevel::WARNING:
      return std::string( "Warning: " );
    case LogLevel::ERROR:
      return std::string( "Error: " );

    case LogLevel::NONE:
    default:
      return std::string( "" );
    }
  }
  std::ofstream stream;
  std::string FileName;
};
//---------------------------------------------------------------
//       LoggerFabric class implementation:
//---------------------------------------------------------------
LoggerInterface* LoggerFabric::GetLogger( LoggerConfig config )
{
  switch( config.GetLogType() )
  {
  case LogInterfaceEnum::NONE:
    return nullptr;
  case LogInterfaceEnum::CONSOLE:
    return new ConsoleLogger();
  case LogInterfaceEnum::FILE:
    return new FileLogger( config.GetLogFilepath() );
  default:
    return nullptr;
  }
}