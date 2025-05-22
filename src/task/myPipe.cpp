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
    dup2( p_stdin[READ], STDIN_FILENO );
    close( p_stdout[READ] );
    dup2( p_stdout[WRITE], STDOUT_FILENO );
    dup2( p_stdout[WRITE], STDERR_FILENO );  // stderr → stdout
    close( p_stdin[READ] );
    close( p_stdout[WRITE] );

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

void freeArgv( char** argv, int argc ) {
  if( argv ) {
    for( int i = 0; i < argc; ++i ) {
      delete[] argv[i];
    }
    delete[] argv;
  }
}

bool MyPipe::Open()
{
  int wordsCount = 0;
  char** tokens = stringToArgv( command, wordsCount );

  pid = popen2( tokens, NULL, &childPInput );
  freeArgv( tokens, wordsCount );

  return pid > 0;
}

int MyPipe::Close()
{
  int status = -1;

  if( childPInput != -1 ) {
    close( childPInput );
    childPInput = -1;
  }

  if( pid > 0 ) {
    waitpid( pid, &status, 0 );
  }

  return status;
}

bool MyPipe::Read( char* buf, int maxSize ) {
  if( childPInput == -1 ) {
    return false;
  }

  ssize_t bytesRead = read( childPInput, buf, sizeof( buf ) - 1 );  // оставляем место для \0
  if( bytesRead > 0 ) {
    buf[bytesRead] = '\0';  // явный нуль-терминатор
  }

  if( bytesRead > 0 ) {
    return true;
  }
  else if( bytesRead == 0 ) {
    // EOF - дочерний процесс закрыл свой конец канала
    close( childPInput );
    childPInput = -1;
    return false;
  }
  else {
    // Ошибка чтения
    close( childPInput );
    childPInput = -1;
    return false;
  }
}