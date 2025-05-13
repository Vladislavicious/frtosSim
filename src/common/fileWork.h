#ifndef MY_FILE_OPERATIONS_H_
#define MY_FILE_OPERATIONS_H_

#include <string>

bool DoFileExist( const std::string& Path );
std::string GetAbsPath( const std::string& RelativePath );
#endif // MY_FILE_OPERATIONS_H_