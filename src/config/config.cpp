#include "config.h"
#include <iostream>

BaseConfig::BaseConfig() :
  example{ ErrorCode::ERR_OK }
{
}

void BaseConfig::smh()
{
  std::cout << "aboba!" << std::endl;
}
