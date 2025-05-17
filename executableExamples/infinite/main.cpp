#include <iostream>

int main()
{
  int cnt = 0;
  while( true )
  {
    for( unsigned int i = 0; i < -2; i++ );
    cnt++;
    std::cout << cnt << std::endl;
  }
}