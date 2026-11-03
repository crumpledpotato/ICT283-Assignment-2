#include "DateIO.h"

std::ostream& operator << (std::ostream& os, const Date & date)
{
    int day;
    int month;
    std::string monthName;
    int year;

    date.GetDay(day);
    date.GetMonth(month);
    date.GetYear(year);

    if (month >= 1 && month <= 12)
    {
        date.GetMonthName(monthName);
        os << day << " " << monthName << " " << year;
    }
    else
    {
        os << day << " " << month << " " << year;
    }

    return os;
}
