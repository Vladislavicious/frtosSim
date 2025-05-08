#ifndef COMMON_H_
#define COMMON_H_

#include "time_sv.h"
//---------------------------------------------------------------
enum class ErrorCode {
  ERR_OK = 0,
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
  std::string TranslateError( ErrorCode error );
private:
  ApplicationGlobalInfo();
  static ApplicationGlobalInfo* GlobalInfoInstance;
  TimeSV startDelta;
};
//---------------------------------------------------------------
#endif // COMMON_H_