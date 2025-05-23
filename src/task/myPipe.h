#ifndef MY_PIPE_H_
#define MY_PIPE_H_
#include <string>
#include <cstdio>

//---------------------------------------------------------------
//       MyPipe class definition:
//---------------------------------------------------------------
class MyPipe
{
public:
  MyPipe() {};
  MyPipe( std::string Command, std::string Mode );
  bool Open();
  int Close();
  bool Kill();

  ~MyPipe() {
    Close();
  }

  bool Read( char* buf, int maxSize );
private:
  int pid{ -1 };
  int childPOutput{ -1 };
  int childPInput{ -1 };
  std::string command{ "" };
  std::string mode{ "" };
};
//---------------------------------------------------------------
#endif // MY_PIPE_H_