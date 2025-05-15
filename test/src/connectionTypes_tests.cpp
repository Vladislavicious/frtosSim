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

void compar( std::string id_str, std::string rxCapacity_str,
  std::string rxMinPacketSize_str, std::string txCapacity_str,
  std::string txMinPacketSize_str, std::string connectsTo_str,
  ConnectionDescriptor expectedDescr )
{
  std::stringstream jsonString;
  jsonString << R"({"id": )" << id_str << "," << std::endl;
  jsonString << R"("rxCapacity": )" << rxCapacity_str << "," << std::endl;
  jsonString << R"("rxMinPacketSize": )" << rxMinPacketSize_str << "," << std::endl;

  jsonString << R"("txCapacity": )" << txCapacity_str << "," << std::endl;
  jsonString << R"("txMinPacketSize": )" << txMinPacketSize_str << "," << std::endl;
  jsonString << R"("connectsTo": )" << connectsTo_str << "\n}";

  json j = json::parse( jsonString.str() );
  auto parsed = j.template get<ConnectionDescriptor>();

  EXPECT_EQ( parsed, expectedDescr );
}
// {



TEST( connectionTypes, readConnectionDescr )
{
  ConnectionIdentificator id;
  id.connectionName = "ab";
  id.connectionType = ConnectionTypeEnum::CNT_SPI;
  id.hostSimulatorName = "hostSim";

  json j = id;

  std::string id_str = j.dump();

  uint32_t rxCapacity = 5;
  uint32_t rxMinPacketSize = 3;
  uint32_t txCapacity = 50;
  uint32_t txMinPacketSize = 30;

  std::string rxCapacity_str{ std::to_string( rxCapacity ) };
  std::string rxMinPacketSize_str{ std::to_string( rxMinPacketSize ) };
  std::string txCapacity_str{ std::to_string( txCapacity ) };
  std::string txMinPacketSize_str{ std::to_string( txMinPacketSize ) };

  ConnectionIdentificator conn = id;
  conn.connectionType = ConnectionTypeEnum::CNT_UART;

  json newJ = conn;

  std::string connectsTo_str = newJ.dump();

  ConnectionDescriptor expectedDescr;
  expectedDescr.id = id;
  expectedDescr.rxCapacity = rxCapacity;
  expectedDescr.rxMinPacketSize = rxMinPacketSize;
  expectedDescr.txCapacity = txCapacity;
  expectedDescr.txMinPacketSize = txMinPacketSize;
  expectedDescr.connectsTo = conn;

  compar( id_str, rxCapacity_str,
    rxMinPacketSize_str, txCapacity_str,
    txMinPacketSize_str, connectsTo_str, expectedDescr );
}