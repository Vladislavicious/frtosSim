#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "buildTask.h"

using namespace std;

static const std::string BuildConfigPath = std::string( TEST_DATA_DIR ) + std::string( "/buildTask/" );
//---------------------------------------------------------------
TEST( buildTaskTest, badMakefileCheck ) {
  static const std::string ExpectedMakefilePath = BuildConfigPath + std::string( "test.mk" );

  BuildConfig config;
  config.CheckConfig( BuildConfigPath + std::string( "buildBadMake.json" ) );
  EXPECT_TRUE( config.IsValid() );

  BuildTask buildTask( config );
  buildTask();

  ErrorCode result = buildTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_MAKE_BUILD );
}
//---------------------------------------------------------------
TEST( buildTaskTest, goodMakefileTest ) {
  static const std::string ExpectedMakefilePath = BuildConfigPath + std::string( "test.mk" );

  BuildConfig config;
  config.CheckConfig( BuildConfigPath + std::string( "buildGoodMake.json" ) );
  EXPECT_TRUE( config.IsValid() );

  BuildTask buildTask( config );
  buildTask();

  ErrorCode result = buildTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
}
//---------------------------------------------------------------