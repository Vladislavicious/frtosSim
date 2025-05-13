#include "buildTask.h"
#include <iostream>
#include <cstdio>
//---------------------------------------------------------------
class MyPipe
{
public:
  MyPipe( std::string Command, std::string Mode )
    : command{ Command }, mode{ Mode }
  {
  }
  bool Open() {
    pipe = popen( command.c_str(), mode.c_str() );
    if( !pipe )
      return false;
    return true;
  }
  int Close() {
    if( pipe )
    {
      int retVal = pclose( pipe );
      pipe = nullptr;
      return retVal;
    }
    return 0;
  }
  ~MyPipe() {
    Close();
  }
  FILE* GetPipe() { return pipe; };
  bool Read( char* buf, int maxSize ) {
    return fgets( buf, maxSize, pipe ) != nullptr;
  };
private:
  FILE* pipe{ nullptr };
  std::string command;
  std::string mode;
};
//---------------------------------------------------------------
//       BuildTask interface implementation:
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
  MyPipe pip( fullCommand, "r" );


  if( !pip.Open() ) {
    std::cerr << "Error invoking make" << std::endl;
    return ErrorCode{ ErrorCodeEnum::ERR_MAKE_INVOKATION };
  }

  char buffer[128];
  std::stringstream result;


  while( pip.Read( buffer, sizeof( buffer ) ) ) {
    result << buffer;
  }

  int status = pip.Close();

  if( status != 0 ) {
    std::cerr << "build error: " << status << std::endl;
    std::cerr << "make output: " << std::endl;
    std::cerr << result.str() << std::endl;

    return ErrorCode{ ErrorCodeEnum::ERR_MAKE_BUILD };
  }

  std::cout << "make output: " << std::endl;
  std::cout << result.str() << std::endl;

  return ErrorCode{ ErrorCodeEnum::ERR_OK };
}
//---------------------------------------------------------------