#ifndef MY_PIPE_H_
#define MY_PIPE_H_
#include <string>
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


#endif // MY_PIPE_H_