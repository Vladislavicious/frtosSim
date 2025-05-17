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
  EXPECT_EQ( t, expectedType );
}

void compar( std::string strType, std::string strConName,
  std::string strHostName, ConnectionIdentificator expected )
{
  std::stringstream jsonString;
  jsonString << R"({"connectionType": )" << '"' << strType << "\"," << std::endl;
  jsonString << R"("hostSimulatorName": )" << '"' << strHostName << "\"," << std::endl;
  jsonString << R"("connectionName": )" << '"' << strConName << "\"\n}";

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

  id.connectionType = ConnectionTypeEnum::CNT_SPI;
  id.connectionName = "1234";
  id.hostSimulatorName = "something with space and!!2";
  compar( "spi", id.connectionName, id.hostSimulatorName, id );
}

TEST( connectionTypes, readNotFullValue )
{
  std::stringstream jsonString;
  jsonString << R"({"connectionType": )" << '"' << "i2c" << "\"," << std::endl;
  jsonString << R"("connectionName": )" << '"' << "name" << "\"\n}";

  json j = json::parse( jsonString.str() );
  EXPECT_THROW( j.template get<ConnectionIdentificator>(), nlohmann::json::out_of_range );
}

void compar( ConnectionDescriptor expectedDescr )
{
  json j1 = expectedDescr.id;

  std::string id_str = j1.dump();
  json newJ = expectedDescr.connectsTo;

  std::string connectsTo_str = newJ.dump();

  std::stringstream jsonString;
  jsonString << R"({"id": )" << id_str << "," << std::endl;
  jsonString << R"("rxCapacity": )" << std::to_string( expectedDescr.rxCapacity ) << "," << std::endl;
  jsonString << R"("rxMinPacketSize": )" << std::to_string( expectedDescr.rxMinPacketSize ) << "," << std::endl;

  jsonString << R"("txCapacity": )" << std::to_string( expectedDescr.txCapacity ) << "," << std::endl;
  jsonString << R"("txMinPacketSize": )" << std::to_string( expectedDescr.txMinPacketSize ) << "," << std::endl;
  jsonString << R"("connectsTo": )" << connectsTo_str << "\n}";

  json j = json::parse( jsonString.str() );
  auto parsed = j.template get<ConnectionDescriptor>();

  EXPECT_EQ( parsed, expectedDescr );

  json converted = expectedDescr;
  EXPECT_EQ( j, converted );
}


TEST( connectionTypes, readConnectionDescr )
{
  ConnectionIdentificator id;
  id.connectionName = "ab";
  id.connectionType = ConnectionTypeEnum::CNT_SPI;
  id.hostSimulatorName = "hostSim";

  uint32_t rxCapacity = 5;
  uint32_t rxMinPacketSize = 3;
  uint32_t txCapacity = 50;
  uint32_t txMinPacketSize = 30;

  ConnectionIdentificator conn = id;
  conn.connectionType = ConnectionTypeEnum::CNT_UART;

  ConnectionDescriptor expectedDescr;
  expectedDescr.id = id;
  expectedDescr.rxCapacity = rxCapacity;
  expectedDescr.rxMinPacketSize = rxMinPacketSize;
  expectedDescr.txCapacity = txCapacity;
  expectedDescr.txMinPacketSize = txMinPacketSize;
  expectedDescr.connectsTo = conn;

  compar( expectedDescr );
}