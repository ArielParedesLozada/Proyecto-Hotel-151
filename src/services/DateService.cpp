#include "services/DateService.h"
#include <ctime>
namespace Services
{
    Models::Date createDate(int year, int month, int date)
    {
        return Models::Date{year, month, date};
    }
    Models::DateInterval createDateInterval(const Models::Date &date1, const Models::Date &date2)
    {
        if (dateGreaterThan(date1, date2))
        {
            return Models::DateInterval{date2, date1};
        }

        return Models::DateInterval{date1, date2};
    }
    bool dateGreaterThan(const Models::Date &date1, const Models::Date &date2)
    {
        if (date1.year != date2.year)
            return date1.year > date2.year;

        if (date1.month != date2.month)
            return date1.month > date2.month;

        return date1.day > date2.day;
    }
    bool overlap(const Models::DateInterval &interval1, const Models::DateInterval &interval2)
    {
        return !dateGreaterThan(interval2.start, interval1.end) && !dateGreaterThan(interval1.start, interval2.end);
    }
    bool isValidDate(const Models::Date &d)
    {
        if (d.month < 1 || d.month > 12)
            return false;

        if (d.day < 1 || d.day > 31)
            return false;

        if (d.year < 1900)
            return false;

        return true;
    }
    Models::Date today()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        return createDate(
            now->tm_year + 1900,
            now->tm_mon + 1,
            now->tm_mday);
    }
    bool isFutureDate(const Models::Date &d)
    {
        Models::Date t = today();
        return dateGreaterThan(d, t);
    }
} // namespace Services
