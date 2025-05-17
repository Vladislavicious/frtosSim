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
  // std::string simRunnerFilepathStr{ "" };
  // std::string simulatorNameStr{ "" };
  // double simulationSpeedRead = 0.0;
  // std::string loggerConfigFilepathStr{ "" };

  // try {
  //   simRunnerFilepathStr = Config.at( "simRunnerFilepath" );
  // }
  // catch( nlohmann::json::out_of_range ) {
  //   return ConfigError( ConfigErrorEnum::NO_RUN_FILEPATH );
  // }

  // try {
  //   simulationSpeedRead = Config.at( "simulationSpeed" );
  // }
  // catch( nlohmann::json::out_of_range ) {
  //   simulationSpeedRead = 1.0;
  // }

  // try {
  //   simulatorNameStr = Config.at( "simulatorName" );
  // }
  // catch( nlohmann::json::out_of_range ) {
  //   return ConfigError( ConfigErrorEnum::NO_SIM_NAME );
  // }

  // try {
  //   loggerConfigFilepathStr = Config.at( "loggerConfigFilepath" );
  // }
  // catch( nlohmann::json::out_of_range ) {
  //   loggerConfigFilepathStr = "";
  // }

  // try {
  //   availableInterfaces = Config.at( "availableInterfaces" );
  // }
  // catch( nlohmann::json::out_of_range ) {
  //   return ConfigError( ConfigErrorEnum::NO_AVAILABLE_INTERFACES );
  // }

  // simRunnerFilepath = simRunnerFilepathStr;
  // simulationSpeed = simulationSpeedRead;
  // simulatorName = simulatorNameStr;
  // loggerConfigFilepath = loggerConfigFilepathStr;

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------

