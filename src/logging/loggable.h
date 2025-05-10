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
  void SetTimestamps( bool Set );

  void Log( const std::string& message );
  void Log( LogLevel level, const std::string& message );
  void Log( ErrorCode code );
private:
  void _Send( const std::string& message );
  void ChangeLogLevel( LogLevel level );

  LoggerInterface* logger;
  bool timestamps{ true };
  LogLevel currentLogLevel{ LogLevel::NONE };
};
//---------------------------------------------------------------
#endif // LOGGABLE_H_