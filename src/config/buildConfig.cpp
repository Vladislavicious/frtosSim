#include "buildConfig.h"
#include "common.h"
//---------------------------------------------------------------
//       BuildConfig class implementation:
//---------------------------------------------------------------
BuildConfig::BuildConfig() :
  buildFilepath{ "" }
{
}
//---------------------------------------------------------------
std::string BuildConfig::GetBuildFilepath()
{
  return buildFilepath;
}
//---------------------------------------------------------------
ConfigError BuildConfig::ReadConfig( const json& Config )
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