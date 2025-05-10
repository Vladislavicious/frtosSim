#ifndef BUILD_TASK_H_
#define BUILD_TASK_H_

#include "common.h"
#include "time_sv.h"
#include "buildConfig.h"

//---------------------------------------------------------------
struct BuildProcess
{

};
//---------------------------------------------------------------
//       BuildTask interface definition:
//---------------------------------------------------------------
// set start time for BuildTask
// BuildTask starts from main
// BuildTask itself is not a std::thread functor

class BuildTask
{
public:
  // BuildTask( BuildConfig config );
  BuildTask();
  void SetInitialTime( TimeSV start );
  TimeSV GetInitialTime();
  bool HasEnded() const;

  TimeSV GetEndTime();

  void operator()();

private:
  bool ended{ false };
  TimeSV startTime{ 0 };
  TimeSV endTime{ 0 };
  ErrorCode result{ ErrorCodeEnum::ERR_TSK_NOT_STARTED };
};
//---------------------------------------------------------------
#endif // BUILD_TASK_H_