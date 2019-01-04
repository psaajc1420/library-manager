#ifndef LIBRARY_MANAGER_DATE_H_
#define LIBRARY_MANAGER_DATE_H_

#include <string>
#include <sstream>

class Date {
 public:
  explicit Date(int day=0, int month=0, int year=0) 
      : day_(day), month_(month), year_(year) {}
  void SetDay(int);
  int GetDay();
  void SetMonth(int);
  int GetMonth();
  void SetYear(int);
  int GetYear();

  // Creates and string representation of a
  // date backwards 
  std::string GetDate();

 private: 
  int day_;
  int month_;
  int year_;
};
inline void Date::SetDay(int day) { day_ = day; }
inline int Date::GetDay() { return day_; }
inline void Date::SetMonth(int month) { month_ = month; }
inline int Date::GetMonth() { return month_; }
inline void Date::SetYear(int year) { year_ = year; }
inline int Date::GetYear() { return year_; }
inline std::string Date::GetDate() {
    std::ostringstream ss;
    ss << year_ << month_ << day_;
    return ss.str();
}
#endif // LIBRARY_MANAGER_DATE_H_