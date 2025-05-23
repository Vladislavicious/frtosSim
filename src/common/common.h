#ifndef COMMON_H_
#define COMMON_H_

#include "time_sv.h"

//---------------------------------------------------------------
bool stringCmpNoCase( const std::string&, const std::string& );
//---------------------------------------------------------------
enum class ErrorCodeEnum {
  ERR_OK,
  ERR_TSK_NOT_STARTED,
  ERR_MAKE_INVOKATION,
  ERR_MAKE_BUILD,
  ERR_SIMULATION_CALL,
  ERR_SIMULATION_ERROR,
  ERR_TASK_KILLED,
  ERR_BAD
};
//---------------------------------------------------------------
//---------------------------------------------------------------
//       ErrorCode class definition:
//---------------------------------------------------------------
//---------------------------------------------------------------
class ErrorCode {
public:
  ErrorCode( ErrorCodeEnum err );
  bool IsOk() const;
  ErrorCodeEnum GetValue() const;
  std::string GetErrorMessage() const;
private:
  ErrorCodeEnum errorValue;
};
//---------------------------------------------------------------
//       ApplicationGlobalInfo class definition:
//---------------------------------------------------------------
class ApplicationGlobalInfo
{
public:
  static ApplicationGlobalInfo& Instance();

  void SetInitialTimeDelta( TimeSV appStartTime );
  TimeSV GetCurrentAppTime();
private:
  ApplicationGlobalInfo();
  static ApplicationGlobalInfo* GlobalInfoInstance;
  TimeSV startDelta;
};
//---------------------------------------------------------------
#endif // COMMON_H_
