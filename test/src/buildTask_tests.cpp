#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "buildTask.h"

using namespace std;

// polling at 50Hz gives almost same results as future.wait() 
//---------------------------------------------------------------
TEST( BuildTask, conceptTest ) {
  std::vector<BuildTask> tasks;
  std::vector<std::future<void>> futures;

  ApplicationGlobalInfo::Instance().SetInitialTimeDelta( TimeSV::Now() );

  tasks.push_back( BuildTask() );
  tasks.push_back( BuildTask() );
  tasks.push_back( BuildTask() );
  for( auto& task : tasks ) {
    task.SetInitialTime( ApplicationGlobalInfo::Instance().GetCurrentAppTime() );
    EXPECT_FALSE( task.HasEnded() );
  }

  // Запускаем задачи в отдельных потоках
  for( auto& task : tasks ) {
    // Используем std::async для получения future (можно и через std::promise)
    futures.push_back( std::async( std::launch::async, [&task]() {
      task();
      } ) );
  }
  // for( auto& future : futures ) {
  //   future.wait();
  // }
  while( true )
  {
    bool ready = true;
    for( auto& task : tasks )
    {
      if( !task.HasEnded() )
        ready = false;
    }

    if( ready )
      break;
    else
      std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
  }

  for( auto& task : tasks ) {
    EXPECT_TRUE( task.HasEnded() );
    std::cout << task.GetEndTime().GetFullTimeStr() << std::endl;
  }
}
//---------------------------------------------------------------