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
  // const std::string MakeCommand = "make -f ";
  // const std::string path = config.GetBuildFilepath();
  // const std::string fullCommand = MakeCommand + path;
  // MyPipe pip( fullCommand, "r" );

  // if( !pip.Open() ) {
  //   if( stream ) {
  //     *stream << "Error invoking make";
  //   }
  //   return ErrorCode{ ErrorCodeEnum::ERR_MAKE_INVOKATION };
  // }

  // char buffer[128];
  // std::stringstream result;


  // while( pip.Read( buffer, sizeof( buffer ) ) ) {
  //   result << buffer;
  // }

  // int status = pip.Close();

  // if( status != 0 ) {
  //   if( stream ) {
  //     *stream << "build error: " << status << std::endl;
  //     *stream << result.str();
  //   }

  //   return ErrorCode{ ErrorCodeEnum::ERR_MAKE_BUILD };
  // }

  // if( stream ) {
  //   *stream << result.str();
  // }

  return ErrorCode{ ErrorCodeEnum::ERR_OK };
}
//---------------------------------------------------------------