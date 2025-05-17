#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "simulatorConfig.h"

using namespace std;

static const std::string simConfigDataPath = std::string( TEST_DATA_DIR ) + std::string( "/simulatorConfig/" );
//---------------------------------------------------------------
TEST( simulatorConfig, GoodConfig ) {
  SimulatorConfig config;
  ConfigError result = config.CheckConfig( simConfigDataPath + std::string( "goodSim.json" ) );

  EXPECT_EQ( result, ConfigError{ ConfigErrorEnum::OK } );

  EXPECT_STREQ( config.GetRunFilepath().c_str(), "file.exe" );
  EXPECT_EQ( config.GetSimulationSpeed(), 0.95 );
  EXPECT_EQ( config.GetSimulatorName(), "mySim" );
  EXPECT_STREQ( config.GetLoggerConfigPath().c_str(), "logConf.json" );

  ConnectionIdentificator id;
  id.connectionName = "aboba";
  id.connectionType = ConnectionTypeEnum::CNT_I2C;
  id.hostSimulatorName = "host";

  ConnectionDescriptor conn1;
  conn1.id = id;
  conn1.rxCapacity = 5;
  conn1.txCapacity = 5;
  conn1.txMinPacketSize = 3;
  conn1.rxMinPacketSize = 3;

  json j = conn1;
  std::vector<ConnectionDescriptor> interfaces{ conn1 };

  EXPECT_EQ( config.GetAvailableInterfaces(), interfaces );
}
//---------------------------------------------------------------
