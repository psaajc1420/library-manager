#include "library-manager/date.h"

Date::Date(int day, int month, int year) {
    SetDay(day);
    SetMonth(month);
    SetYear(year);
}

// Returns a string representation of the date
std::string Date::GetDate() {
    std::ostringstream ss;
    ss << year_ << month_ << day_;
    return ss.str();
}

