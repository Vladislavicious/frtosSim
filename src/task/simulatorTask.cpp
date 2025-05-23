#include "simulatorTask.h"

#include <iostream>
#include <cstdio>
#include <thread>
#include "myProcess.h"
//---------------------------------------------------------------
//       SimulatorTask class implementation:
//---------------------------------------------------------------
SimulatorTask::SimulatorTask( SimulatorConfig Config ) :
  config{ Config },
  simulationSpeed{ config.GetSimulationSpeed() }
{
}
//---------------------------------------------------------------
double SimulatorTask::GetSpeed()
{
  return simulationSpeed;
}
//---------------------------------------------------------------
void SimulatorTask::SetSpeed( double val )
{
  simulationSpeed = val;
  // TODO: actually change speed of simulation?
}
//---------------------------------------------------------------
ErrorCode SimulatorTask::TaskOperation()
{
  const std::string path = config.GetRunFilepath();

  pip = MyProcess( path, "r" );

  if( !pip.Open() ) {
    if( stream ) {
      *stream << "Error calling simulator";
    }
    return ErrorCode{ ErrorCodeEnum::ERR_SIMULATION_CALL };
  }

  char buffer[1024];
  std::stringstream result;

  while( pip.Read( buffer, sizeof( buffer ) ) ) {
    result << buffer;
    if( HasEnded() )
    {
      return ErrorCode{ ErrorCodeEnum::ERR_TASK_KILLED };
    }
  }

  int status = pip.Close();

  if( status != 0 ) {
    if( stream ) {
      *stream << "execution error: " << status << std::endl;
      *stream << result.str();
    }

    return ErrorCode{ ErrorCodeEnum::ERR_MAKE_BUILD };
  }

  if( stream ) {
    *stream << result.str();
  }

  return ErrorCode{ ErrorCodeEnum::ERR_OK };
}
//---------------------------------------------------------------