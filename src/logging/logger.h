#ifndef LOGGING_H_
#define LOGGING_H_

#include <ostream>
#include "loggerConfig.h"

//---------------------------------------------------------------
//       LoggerInterface class definition:
//---------------------------------------------------------------
class LoggerInterface
{
public:
  virtual ~LoggerInterface() {};
  virtual void Output( const std::string& data ) = 0;
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

