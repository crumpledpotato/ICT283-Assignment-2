#include "WeatherRecType.h"

WeatherRecType::WeatherRecType()
{
    m_speed = 0.0;
    m_temperature = 0.0;
    m_solarRad = 0.0;
}

WeatherRecType::WeatherRecType(const Date& date, const Time& time, float speed, float temperature, float solarRad)
{
    m_date = date;
    m_time = time;
    m_speed = speed;
    m_temperature = temperature;
    m_solarRad = solarRad;
}

void WeatherRecType::GetDate(Date& date) const
{
    date = m_date;
}

void WeatherRecType::GetTime(Time& time) const
{
    time = m_time;
}

void WeatherRecType::GetSpeed(float& speed) const
{
    speed = m_speed;
}

void WeatherRecType::GetTemperature(float& temperature) const
{
    temperature = m_temperature;
}

void WeatherRecType::GetSolarRad(float& solarRad) const
{
    solarRad = m_solarRad;
}

void WeatherRecType::SetDate(const Date& date)
{
    m_date = date;
}

void WeatherRecType::SetTime(const Time& time)
{
    m_time = time;
}

void WeatherRecType::SetSpeed(float speed)
{
    m_speed = speed;
}

void WeatherRecType::SetTemperature(float temperature)
{
    m_temperature = temperature;
}

void WeatherRecType::SetSolarRad(float solarRad)
{
    m_solarRad = solarRad;
}

bool WeatherRecType::operator==(const WeatherRecType& other) const
{
    int day1, month1, year1;
    int day2, month2, year2;
    int hour1, minute1, second1;
    int hour2, minute2, second2;

    Date date1, date2;
    Time time1, time2;

    GetDate(date1);
    other.GetDate(date2);

    GetTime(time1);
    other.GetTime(time2);

    date1.GetDay(day1);
    date1.GetMonth(month1);
    date1.GetYear(year1);
    date2.GetDay(day2);
    date2.GetMonth(month2);
    date2.GetYear(year2);

    time1.GetHour(hour1);
    time1.GetMinute(minute1);
    time1.GetSecond(second1);
    time2.GetHour(hour2);
    time2.GetMinute(minute2);
    time2.GetSecond(second2);

    return (day1 == day2 && month1 == month2 && year1 == year2 &&
        hour1 == hour2 && minute1 == minute2 && second1 == second2);
}

bool WeatherRecType::operator<(const WeatherRecType& other) const
{
    Date date1, date2;
    Time time1, time2;

    GetDate(date1);
    other.GetDate(date2);

    GetTime(time1);
    other.GetTime(time2);

    int day1, month1, year1;
    int day2, month2, year2;
    int hour1, minute1, second1;
    int hour2, minute2, second2;

    date1.GetDay(day1);
    date1.GetMonth(month1);
    date1.GetYear(year1);

    date2.GetDay(day2);
    date2.GetMonth(month2);
    date2.GetYear(year2);

    time1.GetHour(hour1);
    time1.GetMinute(minute1);
    time1.GetSecond(second1);

    time2.GetHour(hour2);
    time2.GetMinute(minute2);
    time2.GetSecond(second2);

    if (year1 != year2)
        return year1 < year2;

    if (month1 != month2)
        return month1 < month2;

    if (day1 != day2)
        return day1 < day2;

    if (hour1 != hour2)
        return hour1 < hour2;

    if (minute1 != minute2)
        return minute1 < minute2;

    return second1 < second2;
}
