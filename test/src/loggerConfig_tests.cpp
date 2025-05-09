#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "loggerConfig.h"

using namespace std;

static const std::string configDataPath = std::string( TEST_DATA_DIR ) + std::string( "/config/" );
//---------------------------------------------------------------
TEST( loggerConfig, creation ) {
  LoggerConfig conf;

  EXPECT_STREQ( conf.GetLogFilepath().c_str(), "" );
  EXPECT_EQ( conf.GetLogType(), LogInterfaceEnum::NONE );
}