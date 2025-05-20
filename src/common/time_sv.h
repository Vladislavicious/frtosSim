#ifndef TIME_SV_H_
#define TIME_SV_H_

#include <stdint.h>
#include <string>

//---------------------------------------------------------------
//       TimeSV class definition:
//---------------------------------------------------------------
class TimeSV
{
public:
  typedef uint64_t TimeType;
  static TimeSV Now();
  static TimeSV FromMillis( TimeType millisCount );
  static TimeSV FromSeconds( TimeType secondsCount ) { return FromMillis( secondsCount * 1000 ); };

  explicit TimeSV( TimeType micros );

  void UpdateTime( TimeType unixTime );
  std::string GetTimeStr() const;
  std::string GetFullTimeStr() const;
  TimeType GetMs() const;
  TimeType GetTimePassedSince( TimeType timestamp ) const;
private:
  TimeType milliseconds{ 0 };
};
//---------------------------------------------------------------
TimeSV operator-( const TimeSV&, const TimeSV& );
bool operator==( const TimeSV&, const TimeSV& );
bool operator<( const TimeSV&, const TimeSV& );
bool operator>( const TimeSV&, const TimeSV& );
bool operator>=( const TimeSV&, const TimeSV& );
bool operator<=( const TimeSV&, const TimeSV& );
//---------------------------------------------------------------
#endif // TIME_SV_H_
