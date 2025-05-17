#include "simulatorConfig.h"
#include "common.h"
#include <iostream>
//---------------------------------------------------------------
//       ConnectionIdentificator class implementation:
//---------------------------------------------------------------
void to_json( json& j, const ConnectionIdentificator& t )
{
  j = json{};
  j["connectionName"] = t.connectionName;
  j["hostSimulatorName"] = t.hostSimulatorName;
  j["connectionType"] = t.connectionType;
}
//---------------------------------------------------------------
void from_json( const json& j, ConnectionIdentificator& t )
{
  json en = j.at( "connectionType" );
  t.connectionType = en.template get<ConnectionTypeEnum>();
  t.connectionName = j.at( "connectionName" );
  t.hostSimulatorName = j.at( "hostSimulatorName" );
}
//---------------------------------------------------------------
bool operator==( const ConnectionIdentificator& first,
  const ConnectionIdentificator& second )
{
  return first.connectionType == second.connectionType &&
    first.connectionName == second.connectionName &&
    first.hostSimulatorName == second.hostSimulatorName;
}
//---------------------------------------------------------------
//       ConnectionDescriptor class implementation:
//---------------------------------------------------------------
bool operator==( const ConnectionDescriptor& first, const ConnectionDescriptor& second )
{
  return first.connectsTo == second.connectsTo &&
    first.id == second.id &&
    first.rxCapacity == second.rxCapacity &&
    first.rxMinPacketSize == second.rxMinPacketSize &&
    first.txCapacity == second.txCapacity &&
    first.txMinPacketSize == second.txMinPacketSize;
}
//---------------------------------------------------------------
void to_json( json& j, const ConnectionDescriptor& t )
{
  j = json{};
  j["id"] = t.id;
  j["connectsTo"] = t.connectsTo;
  j["rxCapacity"] = t.rxCapacity;
  j["txCapacity"] = t.txCapacity;
  j["rxMinPacketSize"] = t.rxMinPacketSize;
  j["txMinPacketSize"] = t.txMinPacketSize;
}
//---------------------------------------------------------------
void from_json( const json& j, ConnectionDescriptor& t )
{
  json id = j.at( "id" );
  t.id = id.template get<ConnectionIdentificator>();

  json conn = j.at( "connectsTo" );
  t.connectsTo = conn.template get<ConnectionIdentificator>();

  t.rxCapacity = j.at( "rxCapacity" );
  t.txCapacity = j.at( "txCapacity" );
  t.rxMinPacketSize = j.at( "rxMinPacketSize" );
  t.txMinPacketSize = j.at( "txMinPacketSize" );
}
//---------------------------------------------------------------
//       SimulatorConfig class implementation:
//---------------------------------------------------------------
SimulatorConfig::SimulatorConfig()
{
}
//---------------------------------------------------------------
std::string SimulatorConfig::GetRunFilepath()
{
  return simRunnerFilepath;
}
//---------------------------------------------------------------
double SimulatorConfig::GetSimulationSpeed()
{
  return simulationSpeed;
}
//---------------------------------------------------------------
std::string SimulatorConfig::GetSimulatorName()
{
  return simulatorName;
}
//---------------------------------------------------------------
std::string SimulatorConfig::GetLoggerConfigPath()
{
  return loggerConfigFilepath;
}
//---------------------------------------------------------------
const std::vector<ConnectionDescriptor>& SimulatorConfig::GetAvailableInterfaces()
{
  return availableInterfaces;
}
//---------------------------------------------------------------
ConfigError SimulatorConfig::ReadConfig( const json& Config )
{
  std::string simRunnerFilepathStr{ "" };
  std::string simulatorNameStr{ "" };
  double simulationSpeedRead = 0.0;
  std::string loggerConfigFilepathStr{ "" };

  try {
    simRunnerFilepathStr = Config.at( "simRunnerFilepath" );
  }
  catch( nlohmann::json::out_of_range ) {
    return ConfigError( ConfigErrorEnum::NO_RUN_FILEPATH );
  }

  try {
    simulationSpeedRead = Config.at( "simulationSpeed" );
  }
  catch( nlohmann::json::out_of_range ) {
    simulationSpeedRead = 1.0;
  }

  try {
    simulatorNameStr = Config.at( "simulatorName" );
  }
  catch( nlohmann::json::out_of_range ) {
    return ConfigError( ConfigErrorEnum::NO_SIM_NAME );
  }

  try {
    loggerConfigFilepathStr = Config.at( "loggerConfigFilepath" );
  }
  catch( nlohmann::json::out_of_range ) {
    loggerConfigFilepathStr = "";
  }

  try {
    availableInterfaces = Config.at( "availableInterfaces" );
  }
  catch( nlohmann::json::out_of_range ) {
    return ConfigError( ConfigErrorEnum::NO_AVAILABLE_INTERFACES );
  }

  simRunnerFilepath = simRunnerFilepathStr;
  simulationSpeed = simulationSpeedRead;
  simulatorName = simulatorNameStr;
  loggerConfigFilepath = loggerConfigFilepathStr;

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------

