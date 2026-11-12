#include "TimeIO.h"

ostream& operator << (ostream& os, const Time & time)
{
    int hour;
    int minute;
    int second;

    time.GetHour(hour);
    time.GetMinute(minute);
    time.GetSecond(second);

    if (hour < 10)
    {
        os << "0";
    }
    os << hour << ":";

    if (minute < 10)
    {
        os << "0";
    }
    os << minute << ":";

    if (second < 10)
    {
        os << "0";
    }
    os << second;

    return os;
}
