#pragma once

namespace Models
{
    struct Date
    {
        int year;
        int month;
        int day;
    };
    struct DateInterval
    {
        Date start;
        Date end;
    };
} // namespace Models
