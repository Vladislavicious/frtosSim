#include "time_sv.h"
#include <sstream>
#include <chrono>
#include <iomanip>
//---------------------------------------------------------------
constexpr const char* DATE_FORMAT = "%d.%m.%Y";
constexpr const char* FULL_TIME_FORMAT = "%H:%M:%S:";

//---------------------------------------------------------------
//       TimeSV class implementation:
//---------------------------------------------------------------

//---------------------------------------------------------------

TimeSV::TimeSV( TimeType startTime ) :
  milliseconds{ startTime }
{
}

//---------------------------------------------------------------

void TimeSV::UpdateTime( TimeType unixTime )
{
  milliseconds = unixTime;
}

//---------------------------------------------------------------

TimeSV TimeSV::Now()
{
  auto secondsUTC = std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
  return TimeSV( static_cast< TimeType >( secondsUTC ) );
}

//---------------------------------------------------------------

TimeSV TimeSV::FromMillis( TimeType millisCount )
{
  return TimeSV( millisCount * 1000 );
}

//---------------------------------------------------------------

std::string TimeSV::GetTimeStr() const
{
  using namespace std::chrono;

  std::time_t temp = milliseconds / 1000 / 1000;
  std::tm* t = std::gmtime( &temp );

  std::stringstream stroka;
  stroka << std::put_time( t, DATE_FORMAT );
  return stroka.str();
}

//---------------------------------------------------------------

std::string TimeSV::GetFullTimeStr() const
{
  using namespace std::chrono;

  std::time_t temp = milliseconds / 1000 / 1000;
  std::time_t micros = milliseconds % ( 1000 * 1000 );
  std::tm* t = std::gmtime( &temp );

  std::stringstream stroka;
  stroka << std::put_time( t, FULL_TIME_FORMAT );
  stroka << std::setfill( '0' ) << std::setw( 6 );
  stroka << micros;
  return stroka.str();
}

//---------------------------------------------------------------

TimeSV::TimeType TimeSV::GetMs() const
{
  return milliseconds;
}

//---------------------------------------------------------------

TimeSV::TimeType TimeSV::GetTimePassedSince( TimeType timestamp ) const
{
  return milliseconds - timestamp;
}

//---------------------------------------------------------------
//     TimeSV operations
//---------------------------------------------------------------
TimeSV operator-( const TimeSV& first, const TimeSV& second )
{
  return TimeSV( first.GetTimePassedSince( second.GetMs() ) );
}
//---------------------------------------------------------------
bool operator==( const TimeSV& first, const TimeSV& second )
{
  return first.GetMs() == second.GetMs();
}
//---------------------------------------------------------------
bool operator<( const TimeSV& first, const TimeSV& second )
{
  return first.GetMs() < second.GetMs();
}
//---------------------------------------------------------------
bool operator>( const TimeSV& first, const TimeSV& second )
{
  return first.GetMs() > second.GetMs();
}
//---------------------------------------------------------------
bool operator>=( const TimeSV& first, const TimeSV& second )
{
  return ( first > second ) || ( first == second );
}
bool operator<=( const TimeSV& first, const TimeSV& second )
{
  return ( first < second ) || ( first == second );
}
//---------------------------------------------------------------