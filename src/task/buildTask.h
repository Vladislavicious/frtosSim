#ifndef BUILD_TASK_H_
#define BUILD_TASK_H_

#include "common.h"
#include "taskInterface.h"
#include "buildConfig.h"

//---------------------------------------------------------------
//       BuildTask class definition:
//---------------------------------------------------------------
class BuildTask : public TaskInterface
{
public:
  /// @param config should already be validated
  explicit BuildTask( BuildConfig Config );
private:
  ErrorCode TaskOperation() override;
  BuildConfig config;
};
//---------------------------------------------------------------
#endif // BUILD_TASK_H_