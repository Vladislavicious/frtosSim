#ifndef CONFIG_H_
#define CONFIG_H_

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "common.h"

//---------------------------------------------------------------
enum class ConfigError {
  OK,
  BAD_FILE_NAME,
  NO_CONFIG_FILE,
  BAD_JSON_FORMAT,
  FILE_NAME_TOO_LONG,

  HAVENT_CHECKED,
};
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
private:
  ConfigError _CheckConfig( std::string Path );

  /// @brief Parses json data from Path
  /// @return parsed json object on good file format and empty json object if errors occured
  json Parse( std::string Path );
  ConfigError CheckFileValidity( std::string Path );

  ConfigError configValidity;
};
//---------------------------------------------------------------
#endif // CONFIG_H_