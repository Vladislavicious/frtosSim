#include "common.h"
#include "time.h"

//---------------------------------------------------------------
ApplicationGlobalInfo* ApplicationGlobalInfo::GlobalInfoInstance = nullptr;
//---------------------------------------------------------------
//       ApplicationGlobalInfo class impelementation:
//---------------------------------------------------------------
ApplicationGlobalInfo& ApplicationGlobalInfo::Instance() {
  if( ApplicationGlobalInfo::GlobalInfoInstance == nullptr ) {
    ApplicationGlobalInfo::GlobalInfoInstance = new ApplicationGlobalInfo();
  }

  return *ApplicationGlobalInfo::GlobalInfoInstance;

}
//---------------------------------------------------------------
ApplicationGlobalInfo::ApplicationGlobalInfo() :
  startDelta{ 0 }
{
}
//---------------------------------------------------------------
void ApplicationGlobalInfo::SetInitialTimeDelta( TimeSV appStartTime )
{
  startDelta = appStartTime;
}
//---------------------------------------------------------------
TimeSV ApplicationGlobalInfo::GetCurrentAppTime()
{
  return TimeSV::Now() - startDelta;
}
//---------------------------------------------------------------
std::string ApplicationGlobalInfo::TranslateError( ErrorCode error )
{
  const std::string stroka( "UNKNOWN" );

  switch( error )
  {
  case ErrorCode::ERR_OK:
    return std::string( "OK" );
    break;
  default:
    break;
  }

  return stroka;
}
//---------------------------------------------------------------