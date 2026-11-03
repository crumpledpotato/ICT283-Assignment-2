#include "Date.h"

Date::Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}

Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

void Date::GetDay(int & day) const
{
    day = m_day;
}

void Date::GetMonth(int & month) const
{
    month = m_month;
}

void Date::GetYear(int & year) const
{
    year = m_year;
}

void Date::SetDay(int day)
{
    m_day = day;
}

void Date::SetMonth(int month)
{
    m_month = month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

void Date::GetMonthName (std::string& monthName) const
{
    switch (m_month)
    {
    case 1 :
        monthName = "January";
        break;
    case 2 :
        monthName = "February";
        break;
    case 3 :
        monthName = "March";
        break;
    case 4 :
        monthName = "April";
        break;
    case 5 :
        monthName = "May";
        break;
    case 6 :
        monthName = "June";
        break;
    case 7 :
        monthName = "July";
        break;
    case 8 :
        monthName = "August";
        break;
    case 9 :
        monthName = "September";
        break;
    case 10 :
        monthName = "October";
        break;
    case 11 :
        monthName = "November";
        break;
    case 12 :
        monthName = "December";
        break;
    default :
        monthName = "0";
        break;
    }
}

// Compares two dates chronologically
bool operator<(const Date& lhs, const Date& rhs)
{
    int lhsDay, lhsMonth, lhsYear;
    int rhsDay, rhsMonth, rhsYear;

    lhs.GetDay(lhsDay);
    lhs.GetMonth(lhsMonth);
    lhs.GetYear(lhsYear);

    rhs.GetDay(rhsDay);
    rhs.GetMonth(rhsMonth);
    rhs.GetYear(rhsYear);

    if (lhsYear != rhsYear)
    {
        return lhsYear < rhsYear;
    }

    if (lhsMonth != rhsMonth)
    {
        return lhsMonth < rhsMonth;
    }

    return lhsDay < rhsDay;
}
