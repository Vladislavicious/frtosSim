#ifndef TASK_INTERFACE_H
#define TASK_INTERFACE_H

#include "common.h"
#include "time_sv.h"
#include "myPipe.h"
//---------------------------------------------------------------
//       TaskInterface interface definition:
//---------------------------------------------------------------
class TaskInterface
{
public:
  // TaskInterface( BuildConfig config );
  TaskInterface();
  void SetInitialTime( TimeSV start );
  TimeSV GetInitialTime();
  bool HasEnded() const;

  TimeSV GetEndTime();
  ErrorCode GetResult();
  void SetOutputStream( std::ostream* Stream );

  void operator()();
  void Kill();
protected:
  virtual ErrorCode TaskOperation() = 0;
  std::ostream* stream{ nullptr };
  MyPipe pip;

private:

  bool ended{ false };
  TimeSV startTime{ 0 };
  TimeSV endTime{ 0 };
  ErrorCode result{ ErrorCodeEnum::ERR_TSK_NOT_STARTED };
};
//---------------------------------------------------------------
#endif // TASK_INTERFACE_H