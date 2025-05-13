#include "fileWork.h"
#include <filesystem>

bool DoFileExist( const std::string& Path )
{
  return std::filesystem::exists( Path );
}

std::string GetAbsPath( const std::string& RelativePath )
{
  std::string path = std::filesystem::canonical( RelativePath );
  return path;
}
