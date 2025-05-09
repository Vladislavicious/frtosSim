#include "loggerConfig.h"
#include "common.h"
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
  std::string logTypeStr;
  LogInterfaceEnum type = LogInterfaceEnum::NONE;

  try {
    logTypeStr = Config.at( "logType" );
    type = FromString( logTypeStr );
  }
  catch( nlohmann::json::parse_error ) {
    return ConfigError( ConfigErrorEnum::NO_LOG_TYPE );
  }

  logType = type;
  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------
LogInterfaceEnum LoggerConfig::FromString( const std::string& str )
{
  const std::string TypeConsole( "console" );
  const std::string TypeFile( "file" );

  if( stringCmpNoCase( str, TypeConsole ) )
    return LogInterfaceEnum::CONSOLE;

  if( stringCmpNoCase( str, TypeFile ) )
    return LogInterfaceEnum::FILE;

  return LogInterfaceEnum::NONE;
}
//---------------------------------------------------------------