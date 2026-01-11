#pragma once
#include "models/Date.h"
namespace Services
{
    Models::Date createDate(int year, int month, int date);
    Models::DateInterval createDateInterval(const Models::Date &date1, const Models::Date &date2);
    bool dateGreaterThan(const Models::Date &date1, const Models::Date &date2);
    bool overlap(const Models::DateInterval &interval1, const Models::DateInterval &interval2);
} // namespace Services
