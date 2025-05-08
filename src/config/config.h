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
  HAVENT_CHECKED,
  BAD_JSON_FORMAT,
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
  json Parse( std::string Path );
  ConfigError CheckFileValidity( std::string Path );

  ConfigError configValidity;
};
//---------------------------------------------------------------
#endif // CONFIG_H_