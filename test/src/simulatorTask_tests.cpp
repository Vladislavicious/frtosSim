#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "simulatorTask.h"

using namespace std;

static const std::string SimTaskConfigPath = std::string( TEST_DATA_DIR ) + std::string( "/simulatorTask/" );
//---------------------------------------------------------------
TEST( simulatorTaskTest, goodHalfSecondCreation ) {
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
//---------------------------------------------------------------
TEST( simulatorTaskTest, goodOutput ) {
  SimulatorConfig config;
  config.ParseConfig( SimTaskConfigPath + std::string( "goodOutputTask.json" ) );
  EXPECT_TRUE( config.IsValidated() );

  const std::string expectedStr = "1234567890";
  SimulatorTask simTask( config );

  std::stringstream outputStr;
  simTask.SetOutputStream( &outputStr );

  simTask();

  ErrorCode result = simTask.GetResult();
  EXPECT_EQ( result.GetValue(), ErrorCodeEnum::ERR_OK );

  EXPECT_STREQ( outputStr.str().c_str(), expectedStr.c_str() );
}
//---------------------------------------------------------------
