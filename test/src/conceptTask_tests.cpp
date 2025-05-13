#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "taskInterface.h"

using namespace std;

constexpr const int WAIT_COUNT = 5;
constexpr const int WAIT_PERIOD_MS = 30;

//---------------------------------------------------------------
class ConceptTestTask : public TaskInterface
{
public:
  ConceptTestTask() {};
private:
  ErrorCode TaskOperation() override {
    for( int i = 0; i <= WAIT_COUNT; ++i ) {
      std::this_thread::sleep_for( std::chrono::milliseconds( WAIT_PERIOD_MS ) ); // Имитация работы
    }
    return ErrorCode{ ErrorCodeEnum::ERR_OK };
  };
};
//---------------------------------------------------------------
bool CheckTimeBounds( TimeSV endTime )
{
  const TimeSV upBound{ 1000 * WAIT_PERIOD_MS * WAIT_COUNT * 4 };
  const TimeSV lowBound{ 1000 * WAIT_PERIOD_MS * WAIT_COUNT };
  return ( endTime > lowBound ) && ( endTime < upBound );
}
//---------------------------------------------------------------
// polling at 50Hz gives almost same results as future.wait() 
TEST( conceptTestTask, PollingTest ) {
  std::vector<ConceptTestTask> tasks;
  std::vector<std::future<void>> futures;

  ApplicationGlobalInfo::Instance().SetInitialTimeDelta( TimeSV::Now() );

  tasks.push_back( ConceptTestTask() );
  tasks.push_back( ConceptTestTask() );
  tasks.push_back( ConceptTestTask() );

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
    EXPECT_TRUE( CheckTimeBounds( task.GetEndTime() ) );
  }
}
//---------------------------------------------------------------
TEST( conceptTestTask, asyncWaitTest ) {
  std::vector<ConceptTestTask> tasks;
  std::vector<std::future<void>> futures;

  ApplicationGlobalInfo::Instance().SetInitialTimeDelta( TimeSV::Now() );

  tasks.push_back( ConceptTestTask() );
  tasks.push_back( ConceptTestTask() );
  tasks.push_back( ConceptTestTask() );

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
  for( auto& future : futures ) {
    future.wait();
  }

  for( auto& task : tasks ) {
    EXPECT_TRUE( task.HasEnded() );
    EXPECT_TRUE( CheckTimeBounds( task.GetEndTime() ) );
  }
}
//---------------------------------------------------------------