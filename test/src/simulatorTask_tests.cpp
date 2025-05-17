#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "simulatorTask.h"

using namespace std;

static const std::string SimulatorConfigPath = std::string( TEST_DATA_DIR ) + std::string( "/simulatorTask/" );
//---------------------------------------------------------------
TEST( simulatorTaskTest, creation ) {
  EXPECT_FALSE( true );
}
// TEST( simulatorTaskTest, badMakefileCheck ) {
//     BuildConfig config;
//   config.CheckConfig( BuildConfigPath + std::string( "buildBadMake.json" ) );
//   EXPECT_TRUE( config.IsValid() );

//   BuildTask simulatorTask( config );
//   simulatorTask();

//   ErrorCode result = simulatorTask.GetResult();
//   EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_MAKE_BUILD );
// }
// //---------------------------------------------------------------
// TEST( simulatorTaskTest, goodMakefileTest ) {
//   BuildConfig config;
//   config.CheckConfig( BuildConfigPath + std::string( "buildGoodMake.json" ) );
//   EXPECT_TRUE( config.IsValid() );

//   BuildTask simulatorTask( config );
//   simulatorTask();

//   ErrorCode result = simulatorTask.GetResult();
//   EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
// }
// //---------------------------------------------------------------
// TEST( simulatorTaskTest, checkOutputFromMake ) {
//   BuildConfig config;
//   config.CheckConfig( BuildConfigPath + std::string( "buildEcho.json" ) );
//   EXPECT_TRUE( config.IsValid() );

//   BuildTask simulatorTask( config );

//   std::stringstream outputStr;
//   simulatorTask.SetOutputStream( &outputStr );
//   simulatorTask();

//   ErrorCode result = simulatorTask.GetResult();
//   EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
//   EXPECT_STREQ( "echoing!\n", outputStr.str().c_str() );
// }
// //---------------------------------------------------------------
// TEST( simulatorTaskTest, longBuildTask ) {
//   BuildConfig config;
//   config.CheckConfig( BuildConfigPath + std::string( "buildLong.json" ) );
//   EXPECT_TRUE( config.IsValid() );

//   BuildTask simulatorTask( config );
//   std::stringstream outputStr;
//   simulatorTask.SetOutputStream( &outputStr );
//   simulatorTask();

//   ErrorCode result = simulatorTask.GetResult();
//   EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );

//   TimeSV timeElapsed = simulatorTask.GetEndTime() - simulatorTask.GetInitialTime();
//   EXPECT_TRUE( timeElapsed > TimeSV( 300000 ) );
// }
// //---------------------------------------------------------------