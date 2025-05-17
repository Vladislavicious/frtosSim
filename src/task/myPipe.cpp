#include "myPipe.h"

MyPipe::MyPipe( std::string Command, std::string Mode )
  : command{ Command }, mode{ Mode }
{
}

bool MyPipe::Open()
{
  pipe = popen( command.c_str(), mode.c_str() );
  if( !pipe )
    return false;
  return true;
}

int MyPipe::Close()
{
  if( pipe )
  {
    int retVal = pclose( pipe );
    pipe = nullptr;
    return retVal;
  }
  return 0;
}
