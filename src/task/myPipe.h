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
  ~MyPipe() {
    Close();
  }
  FILE* GetPipe() { return pipe; };
  bool Read( char* buf, int maxSize ) {
    return fgets( buf, maxSize, pipe ) != nullptr;
  };
private:
  FILE* pipe{ nullptr };
  std::string command{ "" };
  std::string mode{ "" };
};
//---------------------------------------------------------------
#endif // MY_PIPE_H_