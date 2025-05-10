#ifndef LOGGING_H_
#define LOGGING_H_

#include <ostream>
#include "loggerConfig.h"

//---------------------------------------------------------------
enum class LogLevel {
  NONE,
  INFO,
  WARNING,
  ERROR
};
//---------------------------------------------------------------
//       LoggerInterface class definition:
//---------------------------------------------------------------
class LoggerInterface
{
public:
  virtual ~LoggerInterface() {};
  void SetLogLevel( LogLevel newLogLevel ) {
    logLevel = newLogLevel;
  };
  LogLevel GetLogLevel() { return logLevel; };
  virtual void Output( const std::string& data ) = 0;
private:
  LogLevel logLevel{ LogLevel::NONE };
};
//---------------------------------------------------------------
//       LoggerFabric class definition:
//---------------------------------------------------------------
class LoggerFabric
{
public:
  static LoggerInterface* GetLogger( LoggerConfig config );
};
//---------------------------------------------------------------
//---------------------------------------------------------------

#endif // LOGGING_H_

