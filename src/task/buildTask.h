#ifndef BUILD_TASK_H_
#define BUILD_TASK_H_

#include "common.h"
#include "taskInterface.h"
#include "buildConfig.h"
// set start time for BuildTask
// BuildTask starts from main
// BuildTask itself is not a std::thread functor
//---------------------------------------------------------------
//       BuildTask class definition:
//---------------------------------------------------------------
class BuildTask : public TaskInterface
{
public:
  /// @param config should already be validated
  explicit BuildTask( BuildConfig Config );
  void SetOutputStream( std::ostream* Stream );
private:
  ErrorCode TaskOperation() override;
  BuildConfig config;
  std::ostream* stream{ nullptr };
};
//---------------------------------------------------------------
#endif // BUILD_TASK_H_