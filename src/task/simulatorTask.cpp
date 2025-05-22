#include "simulatorTask.h"

#include <iostream>
#include <cstdio>
#include "myPipe.h"
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
  // at this point, executable is checked 

  const std::string path = config.GetRunFilepath();

  pip = MyPipe( path, "r" );

  if( !pip.Open() ) {
    if( stream ) {
      *stream << "Error calling simulator";
    }
    return ErrorCode{ ErrorCodeEnum::ERR_SIMULATION_CALL };
  }

  char buffer[128];
  std::stringstream result;

  //TODO: because of this infinite loop, it's hard to reach to pip
  while( pip.Read( buffer, sizeof( buffer ) ) ) {
    result << buffer;
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