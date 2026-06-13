#include "TTime.h"

const TSoftwareVersion TTime_Version(TTIME_V_MAJOR, TTIME_V_MINOR, TTIME_V_PATCH);

const String dayStr[7]       = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const String monStr[12]      = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const String seasonStr[4]    = {"Winter", "Spring", "Summer", "Fall"};
const String todStr[10]      = {"Midnight", "Night", "Dawn", "Sunrise", "Morning", "Noon", "Afternoon", "Sunset", "Dusk", "Night"}; // just to note, we have night twice because one is for before midnight, and once is for after, makes coding easier
const String moonphaseStr[8] = {"New", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full", "Waning Gibbous", "Third Quarter", "Waning Crescent"};


const uint16_t SunEventTime[SER_COUNT][24][2] = {
  { // SER_NORTHEAST
    {444, 1005},
    {442, 1020},
    {415, 1040},
    {395, 1060},
    {380, 1080},
    {360, 1095},
    {390, 1170},
    {370, 1185},
    {350, 1200},
    {335, 1215},
    {330, 1230},
    {325, 1235},
    {330, 1235},
    {340, 1230},
    {360, 1215},
    {375, 1190},
    {390, 1155},
    {405, 1125},
    {420, 1080},
    {435, 1060},
    {400, 1005},
    {415, 995},
    {430, 995},
    {440, 1000}
  },
  { // SER_SOUTHEAST
    {450, 1050},
    {445, 1065},
    {430, 1080},
    {415, 1095},
    {400, 1110},
    {380, 1125},
    {410, 1195},
    {390, 1205},
    {370, 1220},
    {355, 1230},
    {350, 1240},
    {350, 1245},
    {360, 1245},
    {370, 1240},
    {385, 1230},
    {395, 1210},
    {410, 1185},
    {420, 1155},
    {430, 1125},
    {440, 1105},
    {410, 1065},
    {420, 1050},
    {440, 1050},
    {450, 1050}
  },
  { // SER_MIDWEST /////////
    // {440, 1000},
    // {435, 1020},
    // {415, 1050},
    // {395, 1070},
    // {370, 1090},
    // {345, 1110}, //
    // {380, 1180},
    // {360, 1200},
    // {340, 1220},
    // {325, 1235},
    // {320, 1245},
    // {320, 1250},
    // {330, 1245},
    // {340, 1235},
    // {360, 1215},
    // {375, 1190},
    // {395, 1155},
    // {410, 1125},
    // {430, 1080},
    // {445, 1060},
    // {410, 1005},
    // {425, 990},
    // {435, 990},
    // {440, 995}

    {418, 1003},
    {416, 1017},
    {407, 1033},
    {394, 1048},
    {377, 1062},
    {356, 1075},
    {333, 1089},
    {312, 1101},
    {294, 1114},
    {280, 1127},
    {271, 1138},
    {269, 1146},
    {273, 1148},
    {282, 1143},
    {294, 1132},
    {306, 1115},
    {318, 1094},
    {330, 1072},
    {342, 1050},
    {355, 1029},
    {369, 1010},
    {385, 998},
    {399, 992},
    {411, 994}
  },
  { // SER_SOUTH_CENTRAL
    {455, 1040},
    {445, 1055},
    {425, 1080},
    {410, 1100},
    {390, 1115},
    {370, 1130},
    {390, 1200},
    {370, 1215},
    {350, 1230},
    {340, 1245},
    {330, 1250},
    {330, 1255},
    {340, 1250},
    {350, 1245},
    {365, 1230},
    {380, 1210},
    {400, 1180},
    {415, 1150},
    {430, 1125},
    {445, 1105},
    {420, 1050},
    {430, 1035},
    {445, 1035},
    {450, 1040}
  },
  { // SER_MOUNTAIN
    {460, 1025},
    {455, 1040},
    {435, 1070},
    {415, 1090},
    {395, 1110},
    {375, 1125},
    {395, 1200},
    {375, 1215},
    {350, 1235},
    {340, 1245},
    {335, 1250},
    {335, 1255},
    {345, 1250},
    {355, 1240},
    {370, 1220},
    {385, 1195},
    {405, 1155},
    {420, 1125},
    {440, 1080},
    {455, 1060},
    {430, 1020},
    {445, 1010},
    {455, 1010},
    {460, 1015}
  },
  { // SER_SOUTHWEST
    {435, 1025},
    {430, 1040},
    {410, 1070},
    {395, 1090},
    {370, 1110},
    {355, 1125},
    {375, 1200},
    {360, 1215},
    {330, 1235},
    {325, 1245},
    {320, 1250},
    {320, 1255},
    {330, 1250},
    {340, 1240},
    {355, 1220},
    {370, 1200},
    {390, 1165},
    {405, 1135},
    {425, 1095},
    {440, 1075},
    {415, 1030},
    {430, 1020},
    {440, 1020},
    {445, 1025}
  },
  { // SER_NORTHWEST
    {465, 970},
    {455, 990},
    {425, 1030},
    {400, 1050},
    {375, 1080},
    {345, 1100},
    {365, 1180},
    {340, 1200},
    {315, 1230},
    {300, 1250},
    {290, 1260},
    {290, 1265},
    {300, 1260},
    {315, 1250},
    {340, 1225},
    {360, 1195},
    {385, 1150},
    {400, 1110},
    {430, 1065},
    {450, 1040},
    {435, 990},
    {450, 970},
    {465, 970},
    {470, 975}
  },
  { // SER_CALIFORNIA
    {430, 1010},
    {425, 1025},
    {405, 1055},
    {390, 1070},
    {360, 1090},
    {340, 1110},
    {370, 1185},
    {355, 1200},
    {330, 1225},
    {320, 1235},
    {315, 1240},
    {315, 1245},
    {325, 1240},
    {335, 1230},
    {355, 1210},
    {370, 1185},
    {395, 1140},
    {410, 1110},
    {430, 1070},
    {445, 1050},
    {420, 1010},
    {435, 1000},
    {445, 1000},
    {450, 1005}
  }
};




bool isLeapYear(uint16_t year) { 
  // https://learn.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
  if ((year % 4)   != 0) { return false; };
  if ((year % 100) == 0) { return ((year % 400) == 0); };
  return true;
}

uint16_t getNextLeapYear(uint16_t currentyear) { 
  currentyear++;
  while (currentyear <= 5000) { if (isLeapYear(currentyear)) { return currentyear; }; currentyear++; }; 
  return currentyear; 
};

uint8_t getDaysInMonth(uint8_t mon, uint16_t year) { 
  if (mon == FEBRUARY) { return isLeapYear(year) ? 29 : 28; };
  if (mon == APRIL || mon == JUNE || mon == SEPTEMBER || mon == NOVEMBER) { return 30; }
  return 31;
}

uint16_t getDaysInYear(uint16_t year) { return isLeapYear(year) ? 366 : 365; }

uint16_t getDayOfYear(uint16_t year, uint8_t mon, uint8_t day) {
  uint16_t doy = uint16_t(day);
  if (mon > JANUARY) { for (uint8_t m = JANUARY; m <= mon-1; m++) { doy+=uint16_t(getDaysInMonth(m, year)); }; };
  return doy;
}

uint8_t getDayOfWeek(uint16_t year, uint8_t mon, uint8_t day) {
  uint16_t shortyear = year % 100;
  uint8_t ycode = (shortyear + (shortyear/4)) % 7;

  uint8_t mcode = 0;
  if      (mon == 2 || mon == 3 || mon == 11) { mcode = 3; }
  else if (mon == 4 || mon == 7)              { mcode = 6; }
  else if (mon == 9 || mon == 12)             { mcode = 5; }
  else if (mon == 5)                          { mcode = 1; }
  else if (mon == 6)                          { mcode = 4; }
  else if (mon == 8)                          { mcode = 2; };

  uint8_t ccode = 0;
  if      (year >= 1700 && year <= 1799) { ccode = 4; }
  else if (year >= 1800 && year <= 1899) { ccode = 2; }
  else if (year >= 2000 && year <= 2099) { ccode = 6; };

  uint8_t leapmod = (isLeapYear(year) && (mon == 1 || mon == 2)) ? 1 : 0;

  return ((ycode + mcode + ccode + day - leapmod) % 7) + 1;
}

uint8_t getSeason(uint8_t mon, uint8_t day) {
  /*
    spring starts 3/20
    summer starts 6/20
    fall   starts 9/22
    winter starts 12/21
  */
  if (mon < 3  || (mon == 3  && day < 20)) { return WINTER; };
  if (mon < 6  || (mon == 6  && day < 20)) { return SPRING; };
  if (mon < 9  || (mon == 9  && day < 22)) { return SUMMER; };
  if (mon < 12 || (mon == 12 && day < 21)) { return FALL; };
  return WINTER;
}

bool isDST(uint8_t mon, uint8_t day, uint8_t dow) {
  /*
    DST begins in March    on the second Sunday
    DST ends   in November on the first  Sunday
  */
  dow--; // we are expecting sunday to be 1 and saturday to be 7, and we need sunday to be 0 for the math to work
  if (mon < MARCH || mon > NOVEMBER) { return false; };
  if (mon > MARCH && mon < NOVEMBER) { return true;  };

  if (mon == MARCH) {
    if (day < 8)  { return false; };
    return ((day-7) >= dow);
  };

  if (mon == NOVEMBER) { return (day < dow); };

  return false;
}

bool isValidDate(uint16_t year, uint8_t mon, uint8_t day) { return ((year > 1999 && year < 2100) && (mon > 0 && mon < 13) && (day > 0 && day <= getDaysInMonth(mon,year))); }
bool isValidTime(uint8_t  hour, uint8_t min, uint8_t sec) { return (hour < 24 && min < 60 && sec < 60); }

inline uint16_t getSunEventMinutes(uint16_t year, uint8_t mon, uint8_t day, SunEventRegion region, bool returnsunrise) {
  double  perioddays  = mon == 2 ? 14 : 15;
  bool    secondhalf  = (day > perioddays);
  uint8_t eventperiod = ((mon-1)*2) + (secondhalf ? 1 : 0);

  double thisevent = double(SunEventTime[uint8_t(region)][eventperiod]                            [(returnsunrise ? 0 : 1)]);
  double nextevent = double(SunEventTime[uint8_t(region)][(eventperiod == 23 ? 0 : eventperiod+1)][(returnsunrise ? 0 : 1)]);

  double periodcomplete  = double(secondhalf ? day-perioddays : day) / (secondhalf ? double(::getDaysInMonth(mon, year)) - perioddays : perioddays);
  double eventadjustment = (nextevent-thisevent) * periodcomplete;

  return uint16_t(thisevent + eventadjustment) + (::isDST(mon,day,::getDayOfWeek(year,mon,day)) ? 60 : 0);
}

uint16_t getSunriseMinutes(uint16_t year, uint8_t mon, uint8_t day, SunEventRegion region) { return getSunEventMinutes(year,mon,day,region,true); }
uint16_t getSunsetMinutes( uint16_t year, uint8_t mon, uint8_t day, SunEventRegion region) { return getSunEventMinutes(year,mon,day,region,false); }

TimeOfDay getTimeOfDay(uint16_t currentminutes, uint16_t sunriseminutes, uint16_t sunsetminutes) {
  if (currentminutes < 720) {
    if (currentminutes < 60)                    { return TOD_MIDNIGHT; };
    if (currentminutes < (sunriseminutes - 30)) { return TOD_MORNNIGHT; };
    if (currentminutes < (sunriseminutes - 10)) { return TOD_DAWN; };
    if (currentminutes < (sunriseminutes + 10)) { return TOD_SUNRISE; };
    return TOD_MORNING;
  };
  if (currentminutes < 780)                   { return TOD_NOON; };
  if (currentminutes < (sunsetminutes - 10))  { return TOD_AFTERNOON; };
  if (currentminutes < (sunsetminutes + 10))  { return TOD_SUNSET; };
  if (currentminutes < (sunsetminutes + 30))  { return TOD_DUSK; };
  return TOD_NIGHT;
}

double getJulianDate(uint16_t year, uint8_t mon, uint8_t day) {
  if (mon <= 2) { year--; mon += 12; };

  int A = year / 100;
  int B = (year > 1582 || (year == 1582 && (mon > 10 || (mon == 10 && day >= 15)))) ? (2 - A + A / 4) : 0;

  double jd = floor(365.25 * (year + 4716)) + floor(30.6001 * (mon + 1)) + day + B - 1524.5;

  return jd;
}

uint16_t getTotalMinutes(uint8_t hour, uint8_t min) { return (uint16_t(hour)*60) + uint16_t(min); }

#define KNOWN_NEW_MOON 2451550.1
#define SYNODIC_MONTH  29.53058867
uint8_t getMoonPhase(double juliandate) {
  double phase = fmod((juliandate - KNOWN_NEW_MOON) / SYNODIC_MONTH, 1.0);
  if (phase < 0) phase += 1.0;
  return uint8_t(phase * 8.0 + 0.5) % 8;
}

uint8_t getMoonPhasePercent(double juliandate) {
  double phase = fmod((juliandate - KNOWN_NEW_MOON) / SYNODIC_MONTH, 1.0);
  if (phase < 0) phase += 1.0;
  return uint8_t(phase * 100.0 + 0.5);
}

String getSeasonStr(uint8_t season)       { if (season < WINTER  || season > FALL)     { return ""; }; return seasonStr[season-1]; }
String getMonthStr(uint8_t mon)           { if (mon    < JANUARY || mon    > DECEMBER) { return ""; }; return monStr[mon-1]; }
String getDayStr(uint8_t dow)             { if (dow    > SATURDAY)                     { return ""; }; return dayStr[dow-1]; }
String getTimeOfDayStr(uint8_t tod)       { if (tod    >= TOD_COUNT)                   { return ""; }; return todStr[tod-1]; }
String getMoonPhaseStr(uint8_t moonphase) { if (moonphase > 7)                         { return ""; }; return moonphaseStr[moonphase]; }













TTime::TTime() { reset(); }
TTime::TTime(uint16_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) { setDate(year,mon,day); setTime(hour,min,sec); }

TTime::~TTime() {  }

bool TTime::reset() {
  _year = TTIME_FIRST_YEAR;
  _mon  = 1;
  _day  = 1;
  _hour = 0;
  _min  = 0;
  _sec  = 0;
  
  return true;
}


uint16_t TTime::getYear()   const { return _year; }
uint8_t  TTime::getMon()    const { return _mon; }
uint8_t  TTime::getDay()    const { return _day; }
uint8_t  TTime::getHour()   const { return _hour; }
uint8_t  TTime::getHour12() const { return _hour == 0 ? 12 : _hour > 12 ? _hour - 12 : _hour; }
bool     TTime::isAM()      const { return (_hour < 12); }
uint8_t  TTime::getMin()    const { return _min; }
uint8_t  TTime::getSec()    const { return _sec; }


double   TTime::getJulianDate() { return ::getJulianDate(_year,_mon,_day); }
uint8_t  TTime::getSeason()     { return ::getSeason(_mon,_day); }
String   TTime::getSeasonStr()  { return seasonStr[TTime::getSeason()-1]; };
String   TTime::getMonStr()     { return monStr[_mon-1]; };
String   TTime::getDayStr()     { return dayStr[TTime::getDayOfWeek()-1]; };
bool     TTime::isDST()         { return ::isDST(_mon,_day,TTime::getDayOfWeek()); }
uint8_t  TTime::getMoonPhase()  { return ::getMoonPhase(TTime::getJulianDate()); }


bool TTime::setDate(uint16_t year, uint8_t mon, uint8_t day) { 
  if (year < TTIME_FIRST_YEAR || year > TTIME_LAST_YEAR) { return false; };
  if (mon  < JANUARY || mon > DECEMBER)                  { return false; };
  if (day  < 1 || day > ::getDaysInMonth(mon, year))     { return false; }; 
  
  _year = year; 
  _mon  = mon; 
  _day  = day;
  
  return true; 
}

bool TTime::setTime(uint8_t hour, uint8_t min, uint8_t sec) { 
  if (hour > 23 || min > 59 || sec > 59) { return false; };
  
  _hour = hour; 
  _min  = min; 
  _sec  = sec;

  return true;
}

bool TTime::setFromFatDateTime(uint16_t fdate, uint16_t ftime) {
  _year = ((fdate >> 9) & 0x7F) + 1980;
  _mon  = (fdate >> 5) & 0x0F;
  _day  = fdate & 0x1F;

  _hour = (ftime >> 11) & 0x1F;
  _min  = (ftime >> 5) & 0x3F;
  _sec  = (ftime & 0x1F) * 2; // 2-second resolution
  
  return true;
}



bool     TTime::isLeapYear()      const { return ::isLeapYear(_year); }
bool     TTime::getNextLeapYear() const { return ::getNextLeapYear(_year); }
uint8_t  TTime::getDaysInMonth()  const { return ::getDaysInMonth(_mon,_year); }
uint16_t TTime::getDaysInYear()   const { return ::getDaysInYear(_year); }
uint16_t TTime::getTotalMinutes() const { return ::getTotalMinutes(_hour,_min); }

uint16_t TTime::getDayOfYear() const { return ::getDayOfYear(_year,_mon,_day); }
uint8_t  TTime::getDayOfWeek() const { return ::getDayOfWeek(_year,_mon,_day); }































TTime_Full::TTime_Full() { TTime_Full::reset(); }
TTime_Full::TTime_Full(uint16_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) { resetTTime_Full(); TTime_Full::setDate(year,mon,day); TTime_Full::setTime(hour,min,sec); }
TTime_Full::TTime_Full(const TTime& tt) : TTime(tt) { resetTTime_Full(); }
TTime_Full& TTime_Full::operator=(const TTime& tt) {
  TTime_Full::setDate(tt.getYear(), tt.getMon(), tt.getDay()); 
  TTime_Full::setTime(tt.getHour(), tt.getMin(), tt.getSec());
  return *this;
}


bool TTime_Full::resetTTime_Full() {
  _dateChanged();
  
  _tod = TOD_NOTSET;
  _date = "00/00/0000"; 
  _time = "00:00:00";

  _region         = SER_NORTHEAST;
  _datetimeformat = FORMAT_DATETIME_US24;
  _showcentury    = false;
  _showseconds    = false;

  _datestringset   = false;
  _timestringset   = false;
  return true;
}


bool TTime_Full::reset() {
  TTime::reset();
  TTime_Full::resetTTime_Full();
  return true;
}


double    TTime_Full::getJulianDate()      { if (_jday == 0)          { _jday = TTime::getJulianDate(); }; return _jday; }
TimeOfDay TTime_Full::getTimeOfDay()       { if (_tod  == TOD_NOTSET) { _tod  = ::getTimeOfDay(TTime_Full::getTotalMinutes(), TTime_Full::getSunriseMinutes(), TTime_Full::getSunsetMinutes()); }; return _tod; }
String    TTime_Full::getTimeOfDayStr()    { return todStr[TTime_Full::getTimeOfDay()-1]; }
uint8_t   TTime_Full::getSeason()          { if (_season == 0) { _season = TTime::getSeason(); }; return _season; }
String    TTime_Full::getSeasonStr()       { return seasonStr[TTime_Full::getSeason()-1]; }
uint8_t   TTime_Full::getDayOfWeek() const { if (_dow == 0) { _dow = ::getDayOfWeek(_year,_mon,_day); }; return _dow; }
String    TTime_Full::getDayStr()          { return dayStr[TTime_Full::getDayOfWeek()-1]; }
uint16_t  TTime_Full::getDayOfYear() const { if (_doy == 0) { _doy = ::getDayOfYear(_year,_mon,_day); }; return _doy; }
bool      TTime_Full::isDST()              { if (_isdst == 0) { _isdst = ::isDST(_mon,_day,TTime_Full::getDayOfWeek()) ? 2 : 1; }; return (_isdst == 2); }
uint8_t   TTime_Full::getMoonPhase()       { if (_moonphase == 255) { _moonphase = ::getMoonPhase(TTime_Full::getJulianDate()); }; return _moonphase; }




void TTime_Full::_dateChanged() {
  _moonphase = 0;
  _isdst = 0;
  _season = 0;
  _jday = 0;
  _dow = 0;
  _doy = 0;
  _sunriseminutes = 0;
  _sunsetminutes = 0;
  _datestringset = false;
}


bool TTime_Full::setDate(uint16_t year, uint8_t mon, uint8_t day) {
  if (year == _year && mon == _mon && day == _day) { return true; };
  if (!TTime::setDate(year,mon,day)) { return false; };
  _dateChanged();
  return true;
}

bool TTime_Full::addDate(uint16_t year, uint16_t mon, uint16_t day) {
  if (year + _year < TTIME_FIRST_YEAR || year + _year > TTIME_LAST_YEAR) { return false; }

  uint16_t cyear = _year;

  uint16_t cday = getDayOfYear() + day;
  while (cday > ::getDaysInYear(cyear)) { cday -= ::getDaysInYear(cyear); cyear--; };

  // converting back to month/day format
  uint16_t cmon = 1;
  while (cday > uint16_t(::getDaysInMonth(uint8_t(cmon), cyear))) { cday -= uint16_t(::getDaysInMonth(uint8_t(cmon), cyear)); cmon++; };

  cmon+=mon;
  while (cmon > DECEMBER) { cmon-=DECEMBER; cyear++; };

  cyear+=year;
  if (cyear < TTIME_FIRST_YEAR || cyear > TTIME_LAST_YEAR) { return false; };

  if (cday > uint16_t(::getDaysInMonth(uint8_t(cmon), cyear))) { cday = uint16_t(::getDaysInMonth(uint8_t(cmon), cyear)); };

  return setDate(cyear,uint8_t(cmon),uint8_t(cday));
}

bool TTime_Full::subtractDate(uint16_t year, uint16_t mon, uint16_t day) {
  if (_year - year < TTIME_FIRST_YEAR || _year - year > TTIME_LAST_YEAR) { return false; };
  
  uint16_t cyear = _year;
  uint16_t cday  = getDayOfYear();

  while (day >= cday) { day-=cday; cyear--; cday = ::getDaysInYear(cyear); };
  cday-=day;

  // Convert back to day/month format
  uint16_t cmon = 1;
  while (cday > uint16_t(::getDaysInMonth(uint8_t(cmon),cyear))) { cday-=uint16_t(::getDaysInMonth(uint8_t(cmon),cyear)); cmon++; };

  while (mon >= cmon) { mon-=cmon; cyear--; cmon = DECEMBER; };
  cmon-=mon;

  cyear-=year;
  if (cyear < TTIME_FIRST_YEAR || cyear > TTIME_LAST_YEAR) { return false; };

  if (cday > uint16_t(::getDaysInMonth(uint8_t(cmon),cyear))) { cday = uint16_t(::getDaysInMonth(uint8_t(cmon),cyear)); }
  else if (cday <= 0) { cday = 1; };

  return setDate(cyear,uint8_t(cmon),uint8_t(cday));
}

String TTime_Full::getDate() {
  if (_datestringset) { return _date; };

  bool usformat = (_datetimeformat == FORMAT_DATETIME_US12 || _datetimeformat == FORMAT_DATETIME_US24);

  if (usformat) { _date = (_mon < 10 ? "0" : "") + String(_mon); }
  else          { _date = (_day < 10 ? "0" : "") + String(_day); };

  _date += "/";
  if (!usformat) { _date += (_mon < 10 ? "0" : "") + String(_mon); }
  else           { _date += (_day < 10 ? "0" : "") + String(_day); };

  _date += "/";
  if (_showcentury) { _date += String(_year); }
  else { 
    uint16_t syear = _year % 100;
    _date += (syear < 10 ? "0" : "") + String(syear); 
  };
  
  _datestringset = true;
  return _date;
}




bool TTime_Full::setTime(uint8_t hour, uint8_t min, uint8_t sec) {
  if (hour == _hour && min == _min && sec == _sec) { return true; };
  if (hour != _hour || min != _min) { _tod = TOD_NOTSET; _isdst = 0; }; // prevents us from updating every freaking second, just once a minute
  if (!TTime::setTime(hour,min,sec)) { return false; };
  _timestringset = false;
  return true;
}

bool TTime_Full::addTime(uint8_t hour, uint8_t min, uint8_t sec) { return addTime(hour, min, sec, false); }
bool TTime_Full::addTime(uint8_t hour, uint8_t min, uint8_t sec, bool affectdate) {
  if (hour > 180 || min > 180 || sec > 180) { return false; };

  uint16_t daysadded = 0;
  uint8_t chour = _hour + hour;
  uint8_t cmin  = _min  + min;
  uint8_t csec  = _sec  + sec;

  while (csec  > 59) { csec  -= 60; cmin++; };
  while (cmin  > 59) { cmin  -= 60; chour++; };
  while (chour > 23) { chour -= 24; daysadded++; }

  if (affectdate && daysadded > 0) { if (!addDate(0,0,daysadded)) { return false; }; };
  return setTime(chour,cmin,csec);
}

bool TTime_Full::subtractTime(uint8_t hour, uint8_t min, uint8_t sec) { return subtractTime(hour, min, sec, false); }
bool TTime_Full::subtractTime(uint8_t hour, uint8_t min, uint8_t sec, bool affectdate) {
  if (hour > 180 || min > 180 || sec > 180) { return false; };

  uint8_t dayssubbed = 0;
  uint8_t chour = _hour;
  uint8_t cmin  = _min;
  uint8_t csec  = _sec;

  while (sec  > csec)  { sec  -= csec;  min++;        csec  = 59; }; csec  -= sec;
  while (min  > cmin)  { min  -= cmin;  hour++;       cmin  = 59; }; cmin  -= min;
  while (hour > chour) { hour -= chour; dayssubbed++; chour = 23; }; chour -= hour;

  if (affectdate && dayssubbed > 0) { if (!subtractDate(0,0,dayssubbed)) { return false; }; };
  return setTime(chour,cmin,csec);
}

String TTime_Full::getTime() {
  if (_timestringset) { return _time; };

  if (_datetimeformat == FORMAT_DATETIME_US24 || _datetimeformat == FORMAT_DATETIME_UK24) { _time = _hour < 10 ? "0" : ""; } 
  else                                                                                    { _time = _hour < 10 && _hour > 0 ? " " : ""; };
  _time += String(getHour());

  _time += _min < 10 ? ":0" : ":";
  _time += String(_min);

  if (_showseconds) {
    _time += _sec < 10 ? ":0" : ":";
    _time += String(_sec);
  }

  _timestringset = true;
  return _time;
}




uint16_t TTime_Full::getSunriseMinutes() { if (_sunriseminutes == 0) { _sunriseminutes = ::getSunriseMinutes(_year, _mon, _day, _region); }; return _sunriseminutes; }
uint16_t TTime_Full::getSunsetMinutes()  { if (_sunsetminutes  == 0) { _sunsetminutes  = ::getSunsetMinutes( _year, _mon, _day, _region); }; return _sunsetminutes; }
      

SunEventRegion TTime_Full::getRegion() { return _region; };
bool TTime_Full::setRegion(SunEventRegion region) { if (region >= SER_COUNT) { return false; }; _region = region; _sunriseminutes = 0; _sunsetminutes = 0; _tod = TOD_NOTSET; return true; };
  
bool TTime_Full::setDateFormat(uint8_t dateformat) { 
  if (dateformat != FORMAT_DATE_US && dateformat != FORMAT_DATE_UK) { return false; }; 
  bool timeis24 = (_datetimeformat == FORMAT_DATETIME_US24 || _datetimeformat == FORMAT_DATETIME_UK24);
  _datetimeformat = timeis24 ? (dateformat == FORMAT_DATE_US ? FORMAT_DATETIME_US24 : FORMAT_DATETIME_UK24) : (dateformat == FORMAT_DATE_US ? FORMAT_DATETIME_US12 : FORMAT_DATETIME_UK12); 
  _datestringset = false; 
  return true; 
}
bool TTime_Full::setTimeFormat(uint8_t timeformat) {
  if (timeformat != FORMAT_TIME_12 && timeformat != FORMAT_TIME_24) { return false; }; 
  bool dateisUS = (_datetimeformat == FORMAT_DATETIME_US12 || _datetimeformat == FORMAT_DATETIME_US24);
  _datetimeformat = dateisUS ? (timeformat == FORMAT_TIME_12 ? FORMAT_DATETIME_US12 : FORMAT_DATETIME_US24) : (timeformat == FORMAT_TIME_12 ? FORMAT_DATETIME_UK12 : FORMAT_DATETIME_UK24); 
  _timestringset = false; 
  return true; 
}
bool TTime_Full::showCentury(bool show) { _datestringset = (_showcentury == show && _datestringset); _showcentury = show; return true; }
bool TTime_Full::showSeconds(bool show) { _timestringset = (_showseconds == show && _timestringset); _showseconds = show; return true; }