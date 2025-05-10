#include "gtest/gtest.h"
#include "common.h"

using namespace std;
//---------------------------------------------------------------

TEST( Common, globalInfoSingleton ) {
  ApplicationGlobalInfo& info = ApplicationGlobalInfo::Instance();
  ApplicationGlobalInfo& otherInfo = ApplicationGlobalInfo::Instance();

  EXPECT_EQ( &info, &otherInfo );
}
//---------------------------------------------------------------

TEST( Common, initialGlobalInfoTimeZero ) {
  ApplicationGlobalInfo& info = ApplicationGlobalInfo::Instance();
  TimeSV result = info.GetCurrentAppTime() - TimeSV::Now();
  EXPECT_TRUE( result.GetMs() <= 5 );
}
//---------------------------------------------------------------

TEST( Common, passedTimeZero ) {
  ApplicationGlobalInfo& info = ApplicationGlobalInfo::Instance();
  info.SetInitialTimeDelta( TimeSV::Now() );
  TimeSV time = info.GetCurrentAppTime();
  uint32_t passedTime = time.GetMs();

  EXPECT_TRUE( passedTime <= 5 ); // in case few microseconds passed since construction
}
//---------------------------------------------------------------

TEST( Common, timeReallyPassess ) {
  ApplicationGlobalInfo& info = ApplicationGlobalInfo::Instance();
  TimeSV initialTime( TimeSV::Now() );
  info.SetInitialTimeDelta( initialTime );

  for( uint32_t i = 0; i < 10000000; i++ );

  TimeSV afterDelayTime = info.GetCurrentAppTime();
  EXPECT_FALSE( afterDelayTime == initialTime );
}

//---------------------------------------------------------------
TEST( Common, errorOkCodeToString ) {
  ErrorCode result{ ErrorCodeEnum::ERR_OK };
  std::string expectedStr{ "OK" };

  EXPECT_STREQ( result.GetErrorMessage().c_str(), expectedStr.c_str() );
}
//---------------------------------------------------------------