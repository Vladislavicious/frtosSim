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
    std::cout << data;
  };
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
      stream << data;
    }
    stream.flush();
    stream.close();
  };
private:
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