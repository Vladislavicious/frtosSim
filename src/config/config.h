#ifndef CONFIG_H_
#define CONFIG_H_

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "common.h"
#include "fileWork.h"
//---------------------------------------------------------------
enum class ConfigErrorEnum {
  // base
  OK,
  BAD_FILE_NAME,
  NO_CONFIG_FILE,
  BAD_JSON_FORMAT,
  FILE_NAME_TOO_LONG,
  // logger
  NO_LOG_TYPE,
  NO_LOG_FILEPATH,
  // builder
  NO_BUILD_FILEPATH,
  BUILD_FILE_NOT_EXIST,
  // simulator
  NO_RUN_FILEPATH,
  NO_SIM_NAME,
  NO_AVAILABLE_INTERFACES,
  // base
  HAVENT_CHECKED,
};
//---------------------------------------------------------------
//       ConfigError class definition:
//---------------------------------------------------------------
class ConfigError {
public:
  ConfigError( ConfigErrorEnum err );
  bool IsOk() const;
  ConfigErrorEnum GetValue() const;
  std::string GetErrorMessage() const;
private:
  ConfigErrorEnum errorValue;
};
//---------------------------------------------------------------
bool operator==( const ConfigError&, const ConfigError& );
//---------------------------------------------------------------
//       BaseConfig class definition:
//---------------------------------------------------------------
class BaseConfig
{
public:
  BaseConfig();
  ConfigError CheckConfig( std::string Path );
  bool IsValid() const;
protected:
  virtual ConfigError ReadConfig( const json& Config ) = 0;
  std::string GetPath();
private:
  ConfigError _CheckConfig( std::string Path );

  /// @brief Parses json data from Path
  /// @return parsed json object on good file format and empty json object if errors occured
  json Parse( std::string Path );
  ConfigError CheckFileValidity( std::string Path );

  ConfigError configValidity;
  std::string path;
};
//---------------------------------------------------------------
#endif // CONFIG_H_