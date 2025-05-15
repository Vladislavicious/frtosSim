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

