#ifndef BUILD_CONFIG_H_
#define BUILD_CONFIG_H_

#include "config.h"

//---------------------------------------------------------------
//       BuildConfig class definition:
//---------------------------------------------------------------
class BuildConfig : public BaseConfig
{
public:
  BuildConfig();
  std::string GetBuildFilepath();
private:
  ConfigError ReadConfig( const json& Config ) override;
  std::string buildFilepath;
};
//---------------------------------------------------------------
#endif // BUILD_CONFIG_H_
