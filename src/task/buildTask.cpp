#include "buildTask.h"
#include <iostream>
#include <cstdio>
//---------------------------------------------------------------
//       BuildTask class implementation:
//---------------------------------------------------------------
BuildTask::BuildTask( BuildConfig Config ) :
  config{ Config }
{
}
//---------------------------------------------------------------
ErrorCode BuildTask::TaskOperation()
{
  const std::string MakeCommand = "make -f ";
  const std::string path = config.GetBuildFilepath();
  const std::string fullCommand = MakeCommand + path;

  pip = MyPipe( fullCommand, "r" );

  if( !pip.Open() ) {
    if( stream ) {
      *stream << "Error invoking make";
    }
    return ErrorCode{ ErrorCodeEnum::ERR_MAKE_INVOKATION };
  }

  char buffer[128];
  std::stringstream result;


  while( pip.Read( buffer, sizeof( buffer ) ) ) {
    result << buffer;
  }

  int status = pip.Close();

  if( status != 0 ) {
    if( stream ) {
      *stream << "build error: " << status << std::endl;
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