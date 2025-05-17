#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "systemConfig.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;


static const std::string systemConfigDataPath = std::string( TEST_DATA_DIR ) + std::string( "/systemConfig/" );

TEST( systemConfig, readGoodTypes )
{
  SystemConfig config;
  ConfigError result = config.CheckConfig( systemConfigDataPath + std::string( "SystemGood.json" ) );
  EXPECT_TRUE( result.IsOk() );

  EXPECT_STREQ( config.GetLoggerConfigPath().c_str(), "log.json" );

  MkConfigStruct expectedFirst;
  expectedFirst.buildConfigPath = "1234";
  expectedFirst.loggerConfigPath = "asdlfk";
  expectedFirst.simulatorConfigPath = "asdjfkjasd";

  EXPECT_EQ( expectedFirst, config.GetMkConfigs()[0] );
}
