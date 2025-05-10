#include "buildTask.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <future>
#include <vector>
#include <chrono>
#include <mutex>
//---------------------------------------------------------------
//       BuildTask interface implementation:
//---------------------------------------------------------------
BuildTask::BuildTask()
{
}
//---------------------------------------------------------------
void BuildTask::SetInitialTime( TimeSV start )
{
  startTime = start;
}
//---------------------------------------------------------------
TimeSV BuildTask::GetInitialTime()
{
  return startTime;
}
//---------------------------------------------------------------
bool BuildTask::HasEnded() const
{
  return ended;
}
//---------------------------------------------------------------
TimeSV BuildTask::GetEndTime()
{
  return endTime;
}
//---------------------------------------------------------------
void BuildTask::operator()()
{
  ended = false;
  for( int i = 0; i <= 10; ++i ) {
    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) ); // Имитация работы
  }
  ended = true;
  endTime = TimeSV::Now();
} 