#include <iostream>
#include <thread>

int main()
{
  int cnt = 0;
  while( true )
  {
    for( unsigned short i = 0; i < -2; i++ )
      std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );

    cnt++;
    std::cout << cnt << std::endl;
  }
}