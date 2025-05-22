#include "myPipe.h"
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

pid_t popen2( char** command, int* infp, int* outfp )
{
  int p_stdin[2], p_stdout[2];
  pid_t pid;

  if( pipe( p_stdin ) != 0 || pipe( p_stdout ) != 0 )
    return -1;

  pid = fork();

  if( pid < 0 )
    return pid;
  else if( pid == 0 )
  {
    close( p_stdin[WRITE] );
    dup2( p_stdin[READ], READ );
    close( p_stdout[READ] );
    dup2( p_stdout[WRITE], WRITE );

    execvp( *command, command );
    perror( "execvp" );
    exit( 1 );
  }

  if( infp == NULL )
    close( p_stdin[WRITE] );
  else
    *infp = p_stdin[WRITE];

  if( outfp == NULL )
    close( p_stdout[READ] );
  else
    *outfp = p_stdout[READ];

  return pid;
}

char** stringToArgv( const std::string& input, int& argc ) {
  std::vector<std::string> tokens;
  std::istringstream iss( input );
  std::string token;

  // Split into tokens
  while( iss >> token ) {
    tokens.push_back( token );
  }

  argc = tokens.size();
  if( argc == 0 ) {
    return nullptr;
  }

  // Allocate array of char pointers
  char** argv = new char* [argc + 1];  // +1 for null terminator

  // Copy each token
  for( int i = 0; i < argc; ++i ) {
    argv[i] = new char[tokens[i].size() + 1];
    strcpy( argv[i], tokens[i].c_str() );
  }

  // Null terminate the array
  argv[argc] = NULL;

  return argv;
}

MyPipe::MyPipe( std::string Command, std::string Mode )
  : command{ Command }, mode{ Mode }
{
}

bool MyPipe::Open()
{
  int wordsCount = 0;
  char** tokens = stringToArgv( command, wordsCount );

  pid = popen2( tokens, NULL, &childPInput );
  delete[] tokens;

  return pid > 0;
}

int MyPipe::Close()
{

  if( childPInput != -1 ) {
    return close( childPInput );
    childPInput = -1;
  }
  int status{ -1 };
  waitpid( pid, &status, 0 );
  return status;
}

bool MyPipe::Read( char* buf, int maxSize ) {
  if( childPInput != -1 )
  {
    volatile int readResult = read( childPInput, buf, maxSize );
    // volatile int readResult1 = read( childPInput, buf, maxSize );
    return readResult > 0;
  }
  return false;
}
