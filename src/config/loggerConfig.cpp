#include "loggerConfig.h"

//---------------------------------------------------------------
//       LoggerConfig class implementation:
//---------------------------------------------------------------
LoggerConfig::LoggerConfig() :
  logType{ LogInterfaceEnum::NONE },
  logFilepath{ "" }
{
}
//---------------------------------------------------------------
LogInterfaceEnum LoggerConfig::GetLogType()
{
  return logType;
}
//---------------------------------------------------------------
std::string LoggerConfig::GetLogFilepath()
{
  return logFilepath;
}
//---------------------------------------------------------------
ConfigError LoggerConfig::ReadConfig( const json& Config )
{
  return ConfigError( ConfigErrorEnum::HAVENT_CHECKED );
}
//---------------------------------------------------------------