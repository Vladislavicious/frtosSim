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
//       SimulatorConfig class implementation:
//---------------------------------------------------------------
SimulatorConfig::SimulatorConfig()
{
}
//---------------------------------------------------------------
ConfigError SimulatorConfig::ReadConfig( const json& Config )
{
  // std::string buildFilepathStr{ "" };

  // try {
  //   buildFilepathStr = Config.at( "buildFilepath" );
  // }
  // catch( nlohmann::json::out_of_range ) {
  //   return ConfigError( ConfigErrorEnum::NO_BUILD_FILEPATH );
  // }

  // bool buildFileExist = DoFileExist( buildFilepathStr );
  // if( buildFileExist )
  // {
  //   buildFilepath = buildFilepathStr;
  // }
  // else
  // {
  //   return ConfigError( ConfigErrorEnum::BUILD_FILE_NOT_EXIST );
  // }

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------

