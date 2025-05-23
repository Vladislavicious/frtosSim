#ifndef MY_PROCESS_H_
#define MY_PROCESS_H_
#include <string>
#include <cstdio>

//---------------------------------------------------------------
//       myProcess class definition:
//---------------------------------------------------------------
class MyProcess
{
public:
  MyProcess() {};
  MyProcess( std::string Command, std::string Mode );
  bool Open();
  int Close();
  bool Kill();

  ~MyProcess() {
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
#endif // MY_PROCESS_H_