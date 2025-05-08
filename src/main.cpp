#include <iostream>
#include "config.h"
#include "time_sv.h"

static const char* const HEADER = "\nTest output\n\n";

int main( int argc, const char* argv[] )
{
  std::cout << HEADER;

  TimeSV vremya{ 0 };
  std::cout << vremya.GetTimeStr() << "\n";

  return 0;
}
