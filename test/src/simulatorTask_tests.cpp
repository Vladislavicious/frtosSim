#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "simulatorTask.h"

using namespace std;

static const std::string SimTaskConfigPath = std::string( TEST_DATA_DIR ) + std::string( "/simulatorTask/" );
//---------------------------------------------------------------
TEST( simulatorTaskTest, goodHalfSecondCreation ) {
  EXPECT_FALSE( false );
  SimulatorConfig config;
  config.ParseConfig( SimTaskConfigPath + std::string( "goodSimTask.json" ) );
  EXPECT_TRUE( config.IsValidated() );

  SimulatorTask simTask( config );

  TimeSV curTime = TimeSV::Now();

  simTask();
  TimeSV secondTime = TimeSV::Now();
  TimeSV executionTime = secondTime - curTime;
  EXPECT_TRUE( executionTime >= TimeSV::FromMillis( 500 ) );

  ErrorCode result = simTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
}
// //---------------------------------------------------------------
// TEST( simulatorTaskTest, goodMakefileTest ) {
//   SimulatorConfig config;
//   config.ParseConfig( SimTaskConfigPath + std::string( "buildGoodMake.json" ) );
//   EXPECT_TRUE( config.IsValidated() );

//   BuildTask simulatorTask( config );
//   simulatorTask();

//   ErrorCode result = simulatorTask.GetResult();
//   EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );
// }
// //---------------------------------------------------------------
// TEST( simulatorTaskTest, checkOutputFromMake ) {
//   SimulatorConfig config;
//   config.ParseConfig( SimTaskConfigPath + std::string( "buildEcho.json" ) );
//   EXPECT_TRUE( config.IsValidated() );

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
//   SimulatorConfig config;
//   config.ParseConfig( SimTaskConfigPath + std::string( "buildLong.json" ) );
//   EXPECT_TRUE( config.IsValidated() );

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