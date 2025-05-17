#include "taskInterface.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <future>
#include <vector>
#include <chrono>
#include <mutex>
//---------------------------------------------------------------
//       TaskInterface interface implementation:
//---------------------------------------------------------------
TaskInterface::TaskInterface()
{
}
//---------------------------------------------------------------
void TaskInterface::SetInitialTime( TimeSV start )
{
  startTime = start;
}
//---------------------------------------------------------------
TimeSV TaskInterface::GetInitialTime()
{
  return startTime;
}
//---------------------------------------------------------------
bool TaskInterface::HasEnded() const
{
  return ended;
}
//---------------------------------------------------------------
TimeSV TaskInterface::GetEndTime()
{
  return endTime;
}
//---------------------------------------------------------------
ErrorCode TaskInterface::GetResult()
{
  return result;
}
//---------------------------------------------------------------
void TaskInterface::SetOutputStream( std::ostream* Stream )
{
  stream = Stream;
}
//---------------------------------------------------------------
void TaskInterface::operator()()
{
  ended = false;
  startTime = ApplicationGlobalInfo::Instance().GetCurrentAppTime();

  result = TaskOperation();

  ended = true;
  endTime = ApplicationGlobalInfo::Instance().GetCurrentAppTime();
}
//---------------------------------------------------------------
void TaskInterface::Kill()
{
  ended = true;
  pip.Close();
  result = ErrorCodeEnum::ERR_TASK_KILLED;
}
//---------------------------------------------------------------