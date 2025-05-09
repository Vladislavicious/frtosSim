#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "buildConfig.h"

using namespace std;

static const std::string buildConfigDataPath = std::string( TEST_DATA_DIR ) + std::string( "/buildConfig/" );
//---------------------------------------------------------------
TEST( buildConfig, creation ) {
  BuildConfig conf;

  EXPECT_STREQ( conf.GetBuildFilepath().c_str(), "" );
}
//---------------------------------------------------------------
TEST( buildConfig, ConfigRead ) {
  BuildConfig conf;
  ConfigError result = conf.CheckConfig( buildConfigDataPath + std::string( "build.json" ) );

  EXPECT_TRUE( result.IsOk() );
  EXPECT_STREQ( conf.GetBuildFilepath().c_str(), "./smh.file" );
}
//---------------------------------------------------------------
TEST( buildConfig, badFileFormat ) {
  BuildConfig conf;
  ConfigError result = conf.CheckConfig( buildConfigDataPath + std::string( "badFile.json" ) );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::NO_BUILD_FILEPATH );
  EXPECT_STREQ( conf.GetBuildFilepath().c_str(), "" );
}
//---------------------------------------------------------------
TEST( buildConfig, badNames ) {
  BuildConfig conf;
  ConfigError result = conf.CheckConfig( buildConfigDataPath + std::string( "badName.json" ) );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::NO_BUILD_FILEPATH );
  EXPECT_STREQ( conf.GetBuildFilepath().c_str(), "" );
}
//---------------------------------------------------------------
