#ifndef LOGGABLE_H_
#define LOGGABLE_H_

#include "logger.h"
//---------------------------------------------------------------
//       Loggable interface definition:
//---------------------------------------------------------------
class Loggable
{
public:
  Loggable();
  void SetLogger( LoggerInterface* Logger );
  void Log( std::string message );
private:
  LoggerInterface* logger;
};
//---------------------------------------------------------------
#endif // LOGGABLE_H_