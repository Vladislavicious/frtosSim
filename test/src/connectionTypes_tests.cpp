#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "simulatorConfig.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

void compar( std::string strType, ConnectionTypeEnum type )
{
  json j = strType;
  auto parsed = j.template get<ConnectionTypeEnum>();
  EXPECT_EQ( parsed, type );

  json converted = type;
  EXPECT_EQ( j, converted );
}

TEST( connectionTypes, readGoodTypes )
{
  compar( "uart", ConnectionTypeEnum::CNT_UART );
  compar( "spi", ConnectionTypeEnum::CNT_SPI );
  compar( "i2c", ConnectionTypeEnum::CNT_I2C );
  compar( "none", ConnectionTypeEnum::CNT_NOT_SET );
}

TEST( connectionTypes, readBadValue ) {
  ConnectionTypeEnum expectedType{ ConnectionTypeEnum::CNT_UNKNOWN };

  json j = "aboba";
  auto t = j.template get<ConnectionTypeEnum>();
  EXPECT_EQ( t, ConnectionTypeEnum::CNT_UNKNOWN );
}

void compar( std::string strType, std::string strConName,
  std::string strHostName, ConnectionIdentificator expected )
{
  std::stringstream jsonString;
  jsonString << R"({"connectionType": )" << '"' << strType << "\",";
  jsonString << R"("hostSimulatorName": )" << '"' << strHostName << "\",";
  jsonString << R"("connectionName": )" << '"' << strConName << "\"}";

  json j = json::parse( jsonString.str() );
  auto parsed = j.template get<ConnectionIdentificator>();

  EXPECT_EQ( parsed, expected );

  json converted = expected;
  EXPECT_EQ( j, converted );
}

TEST( connectionTypes, readConIdentificators )
{
  ConnectionIdentificator id;
  id.connectionName = "aboba";
  id.hostSimulatorName = "zeliboba";
  id.connectionType = ConnectionTypeEnum::CNT_I2C;

  compar( "i2c", id.connectionName, id.hostSimulatorName, id );

  id.connectionType = ConnectionTypeEnum::CNT_NOT_SET;
  id.connectionName = "ustal";
  compar( "none", id.connectionName, id.hostSimulatorName, id );

  id.connectionType = ConnectionTypeEnum::CNT_UART;
  id.connectionName = "";
  id.hostSimulatorName = "";
  compar( "uart", id.connectionName, id.hostSimulatorName, id );
}