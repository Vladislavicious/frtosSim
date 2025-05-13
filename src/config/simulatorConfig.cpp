#include "simulatorConfig.h"
#include "common.h"
#include <iostream>
//---------------------------------------------------------------
constexpr const std::string uartStr = "uart";
constexpr const std::string spiStr = "spi";
constexpr const std::string i2cStr = "i2c";
constexpr const std::string noneStr = "none";
//---------------------------------------------------------------
ConnectionTypeEnum FromString( const std::string& str )
{

  if( stringCmpNoCase( uartStr, str ) )
    return ConnectionTypeEnum::CNT_UART;
  if( stringCmpNoCase( spiStr, str ) )
    return ConnectionTypeEnum::CNT_SPI;
  if( stringCmpNoCase( i2cStr, str ) )
    return ConnectionTypeEnum::CNT_I2C;
  if( stringCmpNoCase( noneStr, str ) )
    return ConnectionTypeEnum::CNT_NOT_SET;

  return ConnectionTypeEnum::CNT_UNKNOWN;
}
//---------------------------------------------------------------
std::string ToString( ConnectionTypeEnum type )
{
  switch( type )
  {
  case ConnectionTypeEnum::CNT_UART:
    return uartStr;
  case ConnectionTypeEnum::CNT_SPI:
    return spiStr;
  case ConnectionTypeEnum::CNT_I2C:
    return i2cStr;
  case ConnectionTypeEnum::CNT_NOT_SET:
    return noneStr;
  default:
    return noneStr;
  }
}
//---------------------------------------------------------------
void to_json( json& j, const ConnectionTypeEnum& t )
{
  j = json{ {"connectionType", ToString( t )} };
}
//---------------------------------------------------------------
void from_json( const json& j, ConnectionTypeEnum& t )
{
  std::string strVal = j.at( "connectionType" );
  t = FromString( strVal );
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

