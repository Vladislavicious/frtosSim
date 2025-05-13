#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "buildTask.h"

using namespace std;

static const std::string BuildConfigPath = std::string( TEST_DATA_DIR ) + std::string( "/buildTask/" );
//---------------------------------------------------------------
TEST( buildTaskTest, badMakefileCheck ) {
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
  BuildConfig config;
  config.CheckConfig( BuildConfigPath + std::string( "buildGoodMake.json" ) );
  EXPECT_TRUE( config.IsValid() );

  BuildTask buildTask( config );
  buildTask();

  ErrorCode result = buildTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
}
//---------------------------------------------------------------
TEST( buildTaskTest, checkOutputFromMake ) {
  BuildConfig config;
  config.CheckConfig( BuildConfigPath + std::string( "buildEcho.json" ) );
  EXPECT_TRUE( config.IsValid() );

  BuildTask buildTask( config );

  std::stringstream outputStr;
  buildTask.SetOutputStream( &outputStr );
  buildTask();

  ErrorCode result = buildTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
  EXPECT_STREQ( "echoing!\n", outputStr.str().c_str() );
}
//---------------------------------------------------------------
TEST( buildTaskTest, longBuildTask ) {
  BuildConfig config;
  config.CheckConfig( BuildConfigPath + std::string( "buildLong.json" ) );
  EXPECT_TRUE( config.IsValid() );

  BuildTask buildTask( config );
  std::stringstream outputStr;
  buildTask.SetOutputStream( &outputStr );
  buildTask();

  ErrorCode result = buildTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );

  TimeSV timeElapsed = buildTask.GetEndTime() - buildTask.GetInitialTime();
  EXPECT_TRUE( timeElapsed > TimeSV( 300000 ) );
}
//---------------------------------------------------------------