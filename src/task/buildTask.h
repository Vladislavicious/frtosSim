#ifndef BUILD_TASK_H_
#define BUILD_TASK_H_

#include "common.h"
#include "taskInterface.h"
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

class BuildTask : public TaskInterface
{
public:
  BuildTask();
private:
  ErrorCode TaskOperation() override;
};
//---------------------------------------------------------------
#endif // BUILD_TASK_H_