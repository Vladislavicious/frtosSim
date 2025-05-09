#ifndef LOGGER_CONFIG_H_
#define LOGGER_CONFIG_H_

#include "config.h"

//---------------------------------------------------------------
enum class LogInterfaceEnum {
  CONSOLE,
  FILE,
  NONE
};
//---------------------------------------------------------------
//       LoggerConfig class definition:
//---------------------------------------------------------------
class LoggerConfig : public BaseConfig
{
public:
  LoggerConfig();
  LogInterfaceEnum GetLogType();
  std::string GetLogFilepath();
private:
  ConfigError ReadConfig( const json& Config ) override;

  LogInterfaceEnum logType;
  std::string logFilepath;
};
//---------------------------------------------------------------
#endif // LOGGER_CONFIG_H_
