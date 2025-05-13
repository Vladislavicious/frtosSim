#include "simulatorConfig.h"
#include "common.h"
//---------------------------------------------------------------
//       SimulatorConfig class implementation:
//---------------------------------------------------------------
SimulatorConfig::SimulatorConfig() :
  buildFilepath{ "" }
{
}
//---------------------------------------------------------------
std::string SimulatorConfig::GetBuildFilepath()
{
  return buildFilepath;
}
//---------------------------------------------------------------
ConfigError SimulatorConfig::ReadConfig( const json& Config )
{
  std::string buildFilepathStr{ "" };

  try {
    buildFilepathStr = Config.at( "buildFilepath" );
  }
  catch( nlohmann::json::out_of_range ) {
    return ConfigError( ConfigErrorEnum::NO_BUILD_FILEPATH );
  }

  bool buildFileExist = DoFileExist( buildFilepathStr );
  if( buildFileExist )
  {
    buildFilepath = buildFilepathStr;
  }
  else
  {
    return ConfigError( ConfigErrorEnum::BUILD_FILE_NOT_EXIST );
  }

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------