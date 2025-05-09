#include "logger.h"
#include <iostream>
#include <fstream>
//---------------------------------------------------------------
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
    stream( fileName ) {
  };
  ~FileLogger() override {};
  void Output( const std::string& data ) override {
    stream << data;
  };
private:
  std::ofstream stream;
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