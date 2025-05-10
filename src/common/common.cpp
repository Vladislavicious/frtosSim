#include "common.h"
#include "time.h"

//---------------------------------------------------------------

bool stringCmpNoCase( const std::string& str1, const std::string& str2 ) {
  return str1.size() == str2.size() && std::equal( str1.begin(), str1.end(), str2.begin(), []( auto a, auto b ) {return std::tolower( a ) == std::tolower( b );} );
}
//---------------------------------------------------------------

//---------------------------------------------------------------
ErrorCode::ErrorCode( ErrorCodeEnum err ) :
  errorValue( err )
{
}
//---------------------------------------------------------------
bool ErrorCode::IsOk() const
{
  return errorValue == ErrorCodeEnum::ERR_OK;
}
//---------------------------------------------------------------
ErrorCodeEnum ErrorCode::GetValue() const
{
  return errorValue;
}
//---------------------------------------------------------------
std::string ErrorCode::GetErrorMessage() const
{
  const std::string stroka( "UNKNOWN" );

  switch( errorValue )
  {
  case ErrorCodeEnum::ERR_OK:
    return std::string( "OK" );
    break;
  default:
    break;
  }
  return stroka;
}
//---------------------------------------------------------------
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