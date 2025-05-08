#include "config.h"
#include <iostream>
#include <fstream>
//---------------------------------------------------------------
BaseConfig::BaseConfig() :
  configValidity{ ConfigError::HAVENT_CHECKED }
{
}
//---------------------------------------------------------------
ConfigError BaseConfig::CheckConfig( std::string Path )
{
  configValidity = _CheckConfig( Path );
  return configValidity;
}
//---------------------------------------------------------------
bool BaseConfig::IsValid() const
{
  return configValidity == ConfigError::OK;
}
//---------------------------------------------------------------
ConfigError BaseConfig::_CheckConfig( std::string Path )
{
  ConfigError result = CheckFileValidity( Path );
  if( result != ConfigError::OK )
    return result;

  json parsed = Parse( Path );
  return ReadConfig( parsed );
}
//---------------------------------------------------------------
json BaseConfig::Parse( std::string Path )
{
  std::ifstream file( Path );
  json data = json::parse( file );
  return json();
}
//---------------------------------------------------------------
ConfigError BaseConfig::CheckFileValidity( std::string Path )
{
  if( !Path.ends_with( ".json" ) )
    return ConfigError::BAD_FILE_NAME;

  if( !std::filesystem::exists( Path ) )
    return ConfigError::NO_CONFIG_FILE;

  return ConfigError::OK;
}
//---------------------------------------------------------------
