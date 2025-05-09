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

  buildFilepath = buildFilepathStr;

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------