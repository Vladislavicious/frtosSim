#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <vector>

#include "config.h"
#include "fileWork.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;
//---------------------------------------------------------------
//       MkConfigStruct class definition:
//---------------------------------------------------------------
struct MkConfigStruct
{
  std::string simulatorConfigPath{ "" };
  std::string buildConfigPath{ "" };
  std::string loggerConfigPath{ "" };
};

bool operator==( const MkConfigStruct&, const MkConfigStruct& );
void to_json( json& j, const MkConfigStruct& t );
void from_json( const json& j, MkConfigStruct& t );
//---------------------------------------------------------------
//       SystemConfig class definition:
//---------------------------------------------------------------
class SystemConfig : public BaseConfig
{
public:
  SystemConfig();
  std::string GetLoggerConfigPath();
  const std::vector<MkConfigStruct>& GetMkConfigs();
private:
  ConfigError ReadConfig( const json& Config ) override;

  std::string systemLogConfigPath{ "" };
  std::vector<MkConfigStruct> mkConfigs;
};
//---------------------------------------------------------------
#endif // SYSTEM_CONFIG_H_
