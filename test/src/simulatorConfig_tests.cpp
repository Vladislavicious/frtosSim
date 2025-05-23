#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "simulatorConfig.h"

using namespace std;

static const std::string simConfigDataPath = std::string( TEST_DATA_DIR ) + std::string( "/simulatorConfig/" );
//---------------------------------------------------------------
TEST( simulatorConfig, GoodConfig ) {
  SimulatorConfig config;
  ConfigError result = config.ParseConfig( simConfigDataPath + std::string( "goodSim.json" ) );

  EXPECT_EQ( result, ConfigError{ ConfigErrorEnum::OK } );

  std::string ExpectedFilepath = simConfigDataPath + std::string( "file.exe" );
  std::string abspath = GetAbsPath( config.GetRunFilepath() );

  EXPECT_STREQ( abspath.c_str(), ExpectedFilepath.c_str() );

  EXPECT_EQ( config.GetSimulationSpeed(), 0.95 );
  EXPECT_EQ( config.GetSimulatorName(), "mySim" );

  ExpectedFilepath = simConfigDataPath + std::string( "logConf.json" );
  abspath = GetAbsPath( config.GetLoggerConfigPath() );

  EXPECT_STREQ( abspath.c_str(), ExpectedFilepath.c_str() );

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
TEST( simulatorConfig, NotFullConfig ) {
  SimulatorConfig config;
  ConfigError result = config.ParseConfig( simConfigDataPath + std::string( "notFullSim.json" ) );

  EXPECT_EQ( result, ConfigError{ ConfigErrorEnum::OK } );

  std::string ExpectedFilepath = simConfigDataPath + std::string( "file.exe" );
  std::string abspath = GetAbsPath( config.GetRunFilepath() );

  EXPECT_STREQ( ExpectedFilepath.c_str(), abspath.c_str() );
  EXPECT_EQ( config.GetSimulationSpeed(), 1.0 );
  EXPECT_EQ( config.GetSimulatorName(), "mySim" );
  EXPECT_STREQ( config.GetLoggerConfigPath().c_str(), "" );

  std::vector<ConnectionDescriptor> interfaces;

  EXPECT_EQ( config.GetAvailableInterfaces(), interfaces );
}
//---------------------------------------------------------------
TEST( simulatorConfig, NoInterfaces ) {
  SimulatorConfig config;
  ConfigError result = config.ParseConfig( simConfigDataPath + std::string( "noInterfaces.json" ) );

  EXPECT_EQ( result, ConfigError{ ConfigErrorEnum::NO_AVAILABLE_INTERFACES } );
}
//---------------------------------------------------------------
TEST( simulatorConfig, BadInterfaces ) {
  SimulatorConfig config;
  ConfigError result = config.ParseConfig( simConfigDataPath + std::string( "BadInterfaces.json" ) );

  EXPECT_EQ( result, ConfigError{ ConfigErrorEnum::NO_AVAILABLE_INTERFACES } );
}
//---------------------------------------------------------------
