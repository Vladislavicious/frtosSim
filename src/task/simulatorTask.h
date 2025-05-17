#ifndef SIMULATOR_TASK_H_
#define SIMULATOR_TASK_H_

#include "common.h"
#include "taskInterface.h"
#include "simulatorConfig.h"

//---------------------------------------------------------------
//       SimulatorTask class definition:
//---------------------------------------------------------------
class SimulatorTask : public TaskInterface
{
public:
  /// @param config should already be validated
  explicit SimulatorTask( SimulatorConfig Config );

  double GetSpeed();
  void SetSpeed( double val );
private:
  ErrorCode TaskOperation() override;
  SimulatorConfig config;
  double simulationSpeed{ 1.0 };
};
//---------------------------------------------------------------
#endif // SIMULATOR_TASK_H_