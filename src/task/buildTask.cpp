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
ErrorCode BuildTask::TaskOperation()
{
  for( int i = 0; i <= 10; ++i ) {
    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) ); // Имитация работы
  }
  return ErrorCode{ ErrorCodeEnum::ERR_OK };
}
//---------------------------------------------------------------