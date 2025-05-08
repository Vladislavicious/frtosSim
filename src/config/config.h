#ifndef CONFIG_H_
#define CONFIG_H_

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "common.h"

//---------------------------------------------------------------
enum class ConfigError {
  OK
};
//---------------------------------------------------------------
//       BaseConfig class definition:
//---------------------------------------------------------------
class BaseConfig
{
public:
  BaseConfig();
  ConfigError CheckConfig( std::string Path );
  bool IsValid();
protected:
  ConfigError ReadConfig( const json& Config );
private:
  json Parse( std::istream& stream );
  bool DoPathExist( std::string Path );
  std::istream OpenFile( std::string Path );

  bool validityChecked{ false };
};
//---------------------------------------------------------------
#endif // CONFIG_H_