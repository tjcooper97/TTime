#ifndef TTIME_H
#define TTIME_H
  #include <Arduino.h>
  #include <TSoftwareVersion.h>
    #define TTIME_V_MAJOR 1
    #define TTIME_V_MINOR 4
    #define TTIME_V_PATCH 1
    extern const TSoftwareVersion TTime_Version;


  enum TimeOfDay {
    TOD_NOTSET,
    TOD_MIDNIGHT,
    TOD_MORNNIGHT,
    TOD_DAWN,
    TOD_SUNRISE,
    TOD_MORNING,
    TOD_NOON,
    TOD_AFTERNOON,
    TOD_SUNSET,
    TOD_DUSK,
    TOD_NIGHT,
    TOD_COUNT
  };
  
  enum SunEventRegion {
    SER_NORTHEAST,     // Scranton, PA
    SER_SOUTHEAST,     // Columbia, SC
    SER_MIDWEST,       // Peoria, IL
    SER_SOUTH_CENTRAL, // Tulsa, OK
    SER_MOUNTAIN,      // Grand Junction, CO
    SER_SOUTHWEST,     // Albuquerque, NM
    SER_NORTHWEST,     // Spokane, WA
    SER_CALIFORNIA,    // Fresno, CA
    SER_COUNT
  };

  enum TimeZone {
    TZ_EASTERN,
    TZ_CENTRAL,
    TZ_MOUNTAIN,
    TZ_PACIFIC,
    TZ_ALASKA,
    TZ_HAWAII,
    TZ_COUNT
  };

  // Restrictions - Note that these restrictions are only being used to make working with a DS3231 simplier, however all methods should work from year 0 onward (no BCE support)
    #define TTIME_FIRST_YEAR 2000
    #define TTIME_LAST_YEAR  2099

  // Date/Time formats
    #define FORMAT_DATETIME_US12 0
    #define FORMAT_DATETIME_US24 1
    #define FORMAT_DATETIME_UK12 2
    #define FORMAT_DATETIME_UK24 3
    #define FORMAT_DATE_US 10
    #define FORMAT_DATE_UK 11
    #define FORMAT_TIME_24 20
    #define FORMAT_TIME_12 21

  // Seasons (don't change this ordering, for example like trying to make this start at 0, that'd be real dumb, cuz we use 0 as a flag -__- so don't try to mess with this crap okay, i'm smarter than you)
    #define WINTER 1
    #define SPRING 2
    #define SUMMER 3
    #define FALL   4
  
  // Days of the week - hey, don't change this ordering if you want that getDayOfWeek stuff to work, cuz it needs Sunday to be the start of the week
    #define SUNDAY    1
    #define MONDAY    2
    #define TUESDAY   3
    #define WEDNESDAY 4
    #define THURSDAY  5
    #define FRIDAY    6
    #define SATURDAY  7

  // Months of the year - make sure you don't mess with this order, like trynna make it start at 0, or you'll jack everything up
    #define JANUARY   1
    #define FEBRUARY  2
    #define MARCH     3
    #define APRIL     4
    #define MAY       5
    #define JUNE      6
    #define JULY      7
    #define AUGUST    8
    #define SEPTEMBER 9
    #define OCTOBER   10
    #define NOVEMBER  11
    #define DECEMBER  12


  
  // A few functions to abstract away boring/annoying date/time type stuff (and to make the TTime class fancier)
  bool      isLeapYear(uint16_t year);
  uint16_t  getNextLeapYear(uint16_t currentyear);
  uint8_t   getDaysInMonth(uint8_t mon, uint16_t year);
  uint16_t  getDaysInYear(uint16_t year);
  uint16_t  getDayOfYear(uint16_t year, uint8_t mon, uint8_t day);
  uint8_t   getDayOfWeek(uint16_t year, uint8_t mon, uint8_t day);
  uint8_t   getSeason(uint8_t mon, uint8_t day);
  bool      isDST(uint8_t mon, uint8_t day, uint8_t dow);
  inline uint16_t getSunEventMinutes(uint16_t year, uint8_t mon, uint8_t day, SunEventRegion region, bool returnsunrise);
  uint16_t  getSunriseMinutes(uint16_t year, uint8_t mon, uint8_t day, SunEventRegion region);
  uint16_t  getSunsetMinutes(uint16_t year, uint8_t mon, uint8_t day, SunEventRegion region);
  TimeOfDay getTimeOfDay(uint16_t currentminutes, uint16_t sunriseminutes, uint16_t sunsetminutes);
  double    getJulianDate(uint16_t year, uint8_t mon, uint8_t day);
  uint16_t  getTotalMinutes(uint8_t hour, uint8_t min);
  uint8_t   getMoonPhase(double juliandate);
  uint8_t   getMoonPhasePercent(double juliandate);
  String    getSeasonStr(uint8_t season);
  String    getMonthStr(uint8_t mon);
  String    getDayStr(uint8_t dow);
  String    getTimeOfDayStr(uint8_t tod);
  String    getMoonPhaseStr(uint8_t moonphase);
  



  class TTime {
    protected:
      uint16_t _year;
      uint8_t  _mon;
      uint8_t  _day;
      uint8_t  _hour;
      uint8_t  _min;
      uint8_t  _sec;

    public:
      TTime();
      TTime(uint16_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);
      virtual ~TTime();
      
      virtual bool reset();
      
      uint16_t getYear()   const;
      uint8_t  getMon()    const;
      uint8_t  getDay()    const;
      uint8_t  getHour()   const;
      uint8_t  getHour12() const;
      bool     isAM()      const;
      uint8_t  getMin()    const;
      uint8_t  getSec()    const;
      
      virtual double   getJulianDate();      
      virtual uint8_t  getSeason();
      virtual String   getSeasonStr();
              String   getMonStr();
      virtual String   getDayStr();
      virtual bool     isDST();
      virtual uint8_t  getMoonPhase();
      
      virtual bool setDate(uint16_t year, uint8_t mon, uint8_t day);
      virtual bool setTime(uint8_t hour, uint8_t min, uint8_t sec);

      bool setFromFatDateTime(uint16_t fdate, uint16_t ftime);

      bool     isLeapYear()      const;
      bool     getNextLeapYear() const;
      uint8_t  getDaysInMonth()  const;
      uint16_t getDaysInYear()   const;
      uint16_t getTotalMinutes() const;
      
      virtual uint8_t  getDayOfWeek() const;
      virtual uint16_t getDayOfYear() const;
  };




  class TTime_Full : public TTime {
    protected:
      uint8_t   _moonphase;
      uint8_t   _isdst;
      TimeOfDay _tod;
      uint8_t   _season;
      double    _jday;
      mutable uint8_t  _dow;
      mutable uint16_t _doy;
      String    _date;
      String    _time;

      uint16_t _sunriseminutes;
      uint16_t _sunsetminutes;

      SunEventRegion _region;
      uint8_t _datetimeformat;
      bool    _showcentury;
      bool    _showseconds;

      bool _datestringset;
      bool _timestringset;

      bool resetTTime_Full();

      void _dateChanged();

    public:
      TTime_Full();
      TTime_Full(uint16_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);
      TTime_Full(const TTime& tt);
      TTime_Full& operator=(const TTime& tt);

      bool reset() override;
      
      double    getJulianDate() override;
      TimeOfDay getTimeOfDay();
      String    getTimeOfDayStr();
      uint8_t   getSeason()    override;
      String    getSeasonStr() override; // look this really aint a const, but it is in the base class so we kinda lie here, because it uses getSeason, which is not const
      uint8_t   getDayOfWeek() const override;
      String    getDayStr()    override; // see note for getseasonstr(), same thing applies here with getdayofweek()
      uint16_t  getDayOfYear() const override;
      bool      isDST()        override;
      uint8_t   getMoonPhase() override;
      
      bool   setDate(uint16_t year, uint8_t mon, uint8_t day) override;
      bool   addDate(uint16_t year, uint16_t mon, uint16_t day);
      bool   subtractDate(uint16_t year, uint16_t mon, uint16_t day);
      String getDate();

      bool   setTime(uint8_t hour, uint8_t min, uint8_t sec) override;
      bool   addTime(uint8_t hour, uint8_t min, uint8_t sec);
      bool   addTime(uint8_t hour, uint8_t min, uint8_t sec, bool affectdate);
      bool   subtractTime(uint8_t hour, uint8_t min, uint8_t sec);
      bool   subtractTime(uint8_t hour, uint8_t min, uint8_t sec, bool affectdate);
      String getTime();

      uint16_t getSunriseMinutes();
      uint16_t getSunsetMinutes();

      SunEventRegion getRegion();
      bool setRegion(SunEventRegion region);
      bool setDateFormat(uint8_t dateformat);
      bool setTimeFormat(uint8_t timeformat);
      bool showCentury(bool show);
      bool showSeconds(bool show);
  };
#endif