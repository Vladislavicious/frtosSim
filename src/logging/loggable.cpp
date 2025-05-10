#include "loggable.h"
#include "common.h"

//---------------------------------------------------------------
//       Loggable interface implementation:
//---------------------------------------------------------------
Loggable::Loggable() :
  logger{ nullptr }
{
}
//---------------------------------------------------------------
void Loggable::SetLogger( LoggerInterface* Logger )
{
  logger = Logger;
}
//---------------------------------------------------------------
void Loggable::SetTimestamps( bool Set )
{
  timestamps = Set;
}
//---------------------------------------------------------------
void Loggable::Log( const std::string& message )
{
  Log( LogLevel::NONE, message );
}
//---------------------------------------------------------------
void Loggable::Log( LogLevel level, const std::string& message )
{
  if( logger != nullptr )
  {
    ChangeLogLevel( level );
    _Send( message );
  }
}
//---------------------------------------------------------------
void Loggable::Log( ErrorCode code )
{
  if( logger != nullptr )
  {
    std::string errCodeStr = code.GetErrorMessage();
    LogLevel level = code.IsOk() ? LogLevel::INFO : LogLevel::ERROR;
    Log( level, errCodeStr );
  }
}
//---------------------------------------------------------------
void Loggable::_Send( const std::string& message )
{
  if( timestamps )
  {
    TimeSV currentTime = ApplicationGlobalInfo::Instance().GetCurrentAppTime();
    std::string timestampStr = currentTime.GetFullTimeStr();
    logger->Output( timestampStr + " " + message );
  }
  else
    logger->Output( message );
}
//---------------------------------------------------------------
void Loggable::ChangeLogLevel( LogLevel level )
{
  if( level != currentLogLevel )
  {
    logger->SetLogLevel( level );
    currentLogLevel = level;
  }
}
//---------------------------------------------------------------