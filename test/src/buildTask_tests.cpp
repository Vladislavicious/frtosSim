#include "gtest/gtest.h"

#include <thread>

#include "buildTask.h"

using namespace std;

//---------------------------------------------------------------
TEST( BuildTask, conceptTest ) {
  BuildTask buildTask;
  EXPECT_FALSE( buildTask.HasEnded() );

  buildTask.SetInitialTime( TimeSV( 123 ) );
  std::thread buildThread( buildTask );
  std::cout << "here" << TimeSV::Now().GetFullTimeStr();
  buildThread.join();

  EXPECT_TRUE( buildTask.HasEnded() );
  std::cout << "here" << TimeSV::Now().GetFullTimeStr();
}
//---------------------------------------------------------------