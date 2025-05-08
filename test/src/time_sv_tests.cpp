#include "gtest/gtest.h"
#include "time_sv.h"

using namespace std;

//---------------------------------------------------------------
TEST( TimeSVtest, zeroTime ) {
  TimeSV tim{ 0 };

  string expectedStr = "01.01.1970";
  int comparison = expectedStr.compare( tim.GetTimeStr() );
  EXPECT_EQ( 0, comparison );
}
//---------------------------------------------------------------

TEST( TimeSVtest, curTime ) {
  constexpr uint32_t mayTime = 1746467926;
  constexpr uint64_t mayTimeMs = mayTime * 1000ULL * 1000ULL;
  TimeSV tim{ mayTimeMs };

  string expectedStr = "05.05.2025";
  int comparison = expectedStr.compare( tim.GetTimeStr() );
  EXPECT_EQ( 0, comparison );
}
//---------------------------------------------------------------

TEST( TimeSVtest, passedTime ) {
  constexpr uint64_t mayTime = 1746467926 * 1000ULL * 1000ULL;
  TimeSV tim{ mayTime };

  constexpr uint64_t expectedTimePassed = 10;

  uint64_t timePassed = tim.GetTimePassedSince( mayTime - expectedTimePassed );
  EXPECT_EQ( expectedTimePassed, timePassed );
}
//---------------------------------------------------------------

TEST( TimeSVtest, nowTime ) {
  constexpr uint64_t mayTime = 1746467926 * 1000ULL * 1000ULL;
  TimeSV tim{ TimeSV::Now() };

  EXPECT_TRUE( tim.GetMs() != 0 );
  EXPECT_TRUE( tim.GetMs() > mayTime );
}
//---------------------------------------------------------------

TEST( TimeSVtest, TimeSvMinus ) {
  constexpr uint64_t mayTime = 1746467926 * 1000ULL * 1000ULL;
  TimeSV tim1{ mayTime };

  const uint64_t expectedResult = 10;
  TimeSV tim2{ mayTime - expectedResult };

  TimeSV result = tim1 - tim2;
  EXPECT_EQ( expectedResult, result.GetMs() );
}
//---------------------------------------------------------------
TEST( TimeSVtest, TimeSvEqual ) {
  constexpr uint64_t mayTime = 1746467926 * 1000ULL * 1000ULL;
  TimeSV tim1{ mayTime };
  TimeSV tim2{ mayTime };

  EXPECT_TRUE( tim1 == tim2 );
}
//---------------------------------------------------------------
TEST( TimeSVtest, TimeSvNotEqual ) {
  constexpr uint64_t mayTime = 1746467926 * 1000ULL * 1000ULL;
  TimeSV tim1{ mayTime };
  TimeSV tim2{ mayTime - 1000ULL };

  EXPECT_TRUE( tim1 != tim2 );
}
//---------------------------------------------------------------