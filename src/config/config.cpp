#include "config.h"
#include <iostream>
#include <fstream>
//---------------------------------------------------------------
ConfigError::ConfigError( ConfigErrorEnum err ) :
  errorValue( err )
{
}
//---------------------------------------------------------------
bool ConfigError::IsOk() const
{
  return errorValue == ConfigErrorEnum::OK;
}
//---------------------------------------------------------------
ConfigErrorEnum ConfigError::GetValue() const
{
  return errorValue;
}
//---------------------------------------------------------------
std::string ConfigError::GetErrorMessage() const
{
  return std::string( "UNEMPLEMENTED" );
}
//---------------------------------------------------------------
bool operator==( const ConfigError& first, const ConfigError& second )
{
  return first.GetValue() == second.GetValue();
}
//---------------------------------------------------------------
//       BaseConfig class implementation:
//---------------------------------------------------------------
//---------------------------------------------------------------
BaseConfig::BaseConfig() :
  configValidity{ ConfigError( ConfigErrorEnum::HAVENT_CHECKED ) },
  path{ "" }
{
}
//---------------------------------------------------------------
bool BaseConfig::IsValidated() const
{
  return configValidity.IsOk();
}
//---------------------------------------------------------------
std::string BaseConfig::GetPath()
{
  return path;
}
//---------------------------------------------------------------
ConfigError BaseConfig::ParseConfig( std::string Path )
{
  configValidity = _CheckConfig( Path );
  return configValidity;
}
//---------------------------------------------------------------
ConfigError BaseConfig::_CheckConfig( std::string Path )
{
  ConfigError result = CheckFileValidity( Path );
  if( !result.IsOk() )
    return result;

  path = Path;

  json parsed = Parse( Path );
  return ReadConfig( parsed );
}
//---------------------------------------------------------------
json BaseConfig::Parse( std::string Path )
{
  std::ifstream file( Path );
  json data;
  try {
    data = json::parse( file );
  }
  catch( nlohmann::json::parse_error ) {
    data = json();
  }
  return data;
}
//---------------------------------------------------------------
ConfigError BaseConfig::CheckFileValidity( std::string Path )
{
  constexpr int MAX_PATH_LENGTH = 256;

  if( Path.length() > MAX_PATH_LENGTH )
    return ConfigError( ConfigErrorEnum::FILE_NAME_TOO_LONG );

  if( !Path.ends_with( ".json" ) )
    return ConfigError( ConfigErrorEnum::BAD_FILE_NAME );

  if( !DoFileExist( Path ) )
    return ConfigError( ConfigErrorEnum::NO_CONFIG_FILE );

  return ConfigError( ConfigErrorEnum::OK );
}
//---------------------------------------------------------------
