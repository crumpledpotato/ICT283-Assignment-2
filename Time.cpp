#include "Time.h"

Time::Time()
{
    m_hour = 0;
    m_minute = 0;
    m_second = 0;
}

Time::Time(int hour, int minute, int second)
{
    if (hour >= 0 && hour <= 23)
    {
        m_hour = hour;
    }
    else
    {
        m_hour = 0;
    }

    if (minute >= 0 && minute <= 59)
    {
        m_minute = minute;
    }
    else
    {
        m_minute = 0;
    }

    if (second >= 0 && second <= 59)
    {
        m_second = second;
    }
    else
    {
        m_second = 0;
    }
}

void Time::GetHour(int& hour) const
{
    hour = m_hour;
}

void Time::GetMinute(int& minute) const
{
    minute = m_minute;
}

void Time::GetSecond(int& second) const
{
    second = m_second;
}

void Time::SetHour(int hour)
{
    m_hour = hour;
}

void Time::SetMinute(int minute)
{
    m_minute = minute;
}

void Time::SetSecond(int second)
{
    m_second = second;
}
