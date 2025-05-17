#include "systemConfig.h"
#include "common.h"
#include <iostream>
//---------------------------------------------------------------
//       MkConfigStruct class implementation:
//---------------------------------------------------------------
void to_json( json& j, const MkConfigStruct& t )
{
  j = json{};
  j["simulatorConfigPath"] = t.simulatorConfigPath;
  j["buildConfigPath"] = t.buildConfigPath;
  j["loggerConfigPath"] = t.loggerConfigPath;
}
//---------------------------------------------------------------
void from_json( const json& j, MkConfigStruct& t )
{
  t.simulatorConfigPath = j.at( "simulatorConfigPath" );
  t.buildConfigPath = j.at( "buildConfigPath" );
  t.loggerConfigPath = j.at( "loggerConfigPath" );
}
//---------------------------------------------------------------
bool operator==( const MkConfigStruct& first,
  const MkConfigStruct& second )
{
  return first.simulatorConfigPath == second.simulatorConfigPath &&
    first.buildConfigPath == second.buildConfigPath &&
    first.loggerConfigPath == second.loggerConfigPath;
}
//---------------------------------------------------------------
//       SystemConfig class implementation:
//---------------------------------------------------------------
SystemConfig::SystemConfig()
{
}
//---------------------------------------------------------------
std::string SystemConfig::GetLoggerConfigPath()
{
  return systemLogConfigPath;
}
//---------------------------------------------------------------
const std::vector<MkConfigStruct>& SystemConfig::GetMkConfigs()
{
  return mkConfigs;
}
//---------------------------------------------------------------
ConfigError SystemConfig::ReadConfig( const json& Config )
{
  std::string systemLogConfigPathStr{ "" };

  try {
    systemLogConfigPathStr = Config.at( "systemLogConfigPath" );
  }
  catch( nlohmann::json::out_of_range ) {
    systemLogConfigPathStr = "";
  }

  try {
    mkConfigs = Config.at( "mkConfigs" );
  }
  catch( nlohmann::json::out_of_range ) {
    return ConfigError( ConfigErrorEnum::NO_CONFIGS );
  }

  systemLogConfigPath = systemLogConfigPathStr;

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------

