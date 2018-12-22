#ifndef _DATE__
#define _DATE__

#include <string>
#include <sstream>

class Date {

 public:
  Date(int day=0, int month=0, int year=0);
  void SetDay(int);
  int GetDay();
  void SetMonth(int);
  int GetMonth();
  void SetYear(int);
  int GetYear();
  std::string GetDate();

 private: 
  int day_;
  int month_;
  int year_;
};

// Standard getters and setters
inline void Date::SetDay(int day) { day_ = day; }
inline int Date::GetDay() { return day_; }
inline void Date::SetMonth(int month) { month_ = month; }
inline int Date::GetMonth() { return month_; }
inline void Date::SetYear(int year) { year_ = year; }
inline int Date::GetYear() { return year_; }

#endif