#include "MathHelper.h"
#include "Date.h"
#include "Time.h"
#include "WeatherRecType.h"

#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

float MathHelper::CalculateMean (const Vector<float>& values)
{
    float total = 0.0;
    if (values.Size() == 0)
    {
        return 0.0;
    }

    for (int i = 0; i < values.Size(); i++)
    {
        total += values[i];
    }
    return total / values.Size();

}

float MathHelper::CalculateStdDeviation (const Vector<float>& values, float mean)
{
    if (values.Size() < 2)
    {
        return 0.0;
    }
    float squaredDifferenceSum = 0.0;

    for (int i = 0; i < values.Size(); i++)
    {
        float difference = values[i] - mean;
        squaredDifferenceSum += difference * difference;
    }
    return sqrt(squaredDifferenceSum / (values.Size()-1));
}


bool MathHelper::CalculateWindStats(const WeatherlogType& weather_data)
{
    int inputMonth;
    int inputYear;
    Vector<float> windSpeeds;
    WeatherRecType record;
    int recordMonth;
    int recordYear;

    cout << endl << "Enter a month to search : ";
    while (!(cin >> inputMonth) || inputMonth < 1 || inputMonth > 12)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Invalid input, please enter a number between 1 to 12 : ";
    }
    cout << endl << "Enter a year to search  : ";
    while (!(cin >> inputYear) || inputYear < 1)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Invalid input, please enter a valid year : ";
    }

    // Search for matching month and year

    Date date;
    float speed;
    for (int i = 0; i < weather_data.Size(); i++)
    {
        record = weather_data[i];

        record.GetDate(date);
        record.GetSpeed(speed);
        date.GetMonth(recordMonth);
        date.GetYear(recordYear);

        if (recordMonth == inputMonth && recordYear == inputYear)
        {
            windSpeeds.Insert(windSpeeds.Size(), speed);
        }
    }
    if (windSpeeds.Size() == 0)
    {
        cout << endl << "No matching records for " << inputMonth << " / " << inputYear << " found" << endl;
        return false;
    }
    float mean = CalculateMean(windSpeeds);
    float stdDeviation = CalculateStdDeviation(windSpeeds, mean);

    Date selectedDate(1, inputMonth, inputYear);
    string monthName;
    selectedDate.GetMonthName(monthName);

    cout << endl << "==================================================" << endl;
    cout << "                    STATISTICS" << endl;
    cout << "==================================================" << endl;
    cout << monthName << " " << inputYear << " : " << endl;
    cout << fixed << setprecision(1);
    cout << endl << "Average speed      : " << (mean * 3.6) << "km/h" << endl;
    cout << "Sample stdeviation : " << (stdDeviation * 3.6) << "km/h" << endl << endl;
    return true;
}

bool MathHelper::CalculateTemperatureStats(const WeatherlogType& weather_data)
{
    int inputYear;
    cout << endl << "Enter a year to search  : ";
    while (!(cin >> inputYear) || inputYear < 1)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Invalid input, please enter a valid year : ";
    }

    cout << endl << "==================================================" << endl;
    cout << "              TEMPERATURE STATISTICS" << endl;
    cout << "==================================================" << endl;
    cout << endl << inputYear << endl << endl;

    cout << fixed << setprecision(1);

    Vector<float> monthlyTemperatures[12];
    Date date;
    float temperature;
    int recordMonth;
    int recordYear;

    for (int i =0; i < weather_data.Size(); i++)
    {
        const WeatherRecType& record = weather_data[i];

        record.GetDate(date);
        record.GetTemperature(temperature);
        date.GetMonth(recordMonth);
        date.GetYear(recordYear);

        if (recordYear == inputYear && recordMonth >= 1 && recordMonth <= 12)
        {
            monthlyTemperatures[recordMonth-1].Insert(
                monthlyTemperatures[recordMonth - 1].Size(), temperature);
        }
    }

    for (int month = 1; month <= 12; month++)
    {
        Date selectedDate (1, month, inputYear);
        string monthName;
        selectedDate.GetMonthName(monthName);

        if (monthlyTemperatures[month - 1].Size() > 0)
        {
            float mean = CalculateMean(monthlyTemperatures[month - 1]);
            float stdDeviation = CalculateStdDeviation(monthlyTemperatures[month - 1], mean);
            cout << left << setw(10) << monthName << " : " << mean << " degrees C," << "\t stdev : " << stdDeviation << endl;
        }
        else
        {
            cout << left << setw(10) << monthName << " : No Data" << endl;
        }
    }
    return true;
}

bool MathHelper::CalculateSolarRad(const WeatherlogType& weather_data)
{
    int inputYear;
    cout << endl << "Enter a year to search  : ";
    while (!(cin >> inputYear) || inputYear < 1)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Invalid input, please enter a valid year : ";
    }

    cout << endl << "==================================================" << endl;
    cout << "            SOLAR RADIATION STATISTICS" << endl;
    cout << "==================================================" << endl;
    cout << endl << inputYear << endl << endl;

    cout << fixed << setprecision(1);
    for (int month = 1; month <= 12 ; month++)
    {
        float totalSolar = 0.0;
        WeatherRecType record;
        Date date;
        float solarRad;
        int recordMonth;
        int recordYear;
        for (int i = 0; i < weather_data.Size(); i++)
        {
            record = weather_data[i];
            record.GetDate(date);
            record.GetSolarRad(solarRad);

            date.GetMonth(recordMonth);
            date.GetYear(recordYear);

            if (recordMonth == month && recordYear == inputYear)
            {
                // Condition stated in Assignment brief
                if (solarRad >= 100)
                {
                    totalSolar += solarRad / 6000;
                }
            }
        }
        Date selectedDate (1, month, inputYear);
        string monthName;
        selectedDate.GetMonthName(monthName);

        if (totalSolar > 0)
        {
            cout << left << setw(10) << monthName << " : "<< totalSolar << " kWh/m2" << endl;
        }
        else
        {
            cout << left << setw(10) << monthName << " : No Data" << endl;
        }
    }
     return true;
}

bool MathHelper::TabulateStatistics(const WeatherlogType& weather_data, int inputYear, MonthlyStats monthlyStats[])
{
    for (int month = 1; month <= 12; month++)
    {
        Vector<float> windSpeeds;
        Vector<float> temperatures;
        Vector<float> solarRadiation;

        for (int i = 0; i < weather_data.Size(); i++)
        {
            WeatherRecType record = weather_data[i];

            Date date;
            float speed;
            float temperature;
            float solarRad;

            int recordMonth;
            int recordYear;

            record.GetDate(date);
            record.GetSpeed(speed);
            record.GetTemperature(temperature);
            record.GetSolarRad(solarRad);

            date.GetMonth(recordMonth);
            date.GetYear(recordYear);

            if (recordMonth == month && recordYear == inputYear)
            {
                windSpeeds.Insert(windSpeeds.Size(), speed);
                temperatures.Insert(temperatures.Size(), temperature);

                if (solarRad >= 100)
                {
                    solarRadiation.Insert(solarRadiation.Size(), solarRad);
                }
            }
        }

        // Calculate wind values
        if (windSpeeds.Size() > 0)
        {
            float mean = CalculateMean(windSpeeds);
            float stdDeviation = CalculateStdDeviation(windSpeeds, mean);

            monthlyStats[month - 1].avgWindSpeed = mean * 3.6;
            monthlyStats[month - 1].windStdDeviation = stdDeviation * 3.6;
            monthlyStats[month - 1].hasWindData = true;
        }
        else
        {
            monthlyStats[month - 1].avgWindSpeed = 0.0;
            monthlyStats[month - 1].windStdDeviation = 0.0;
            monthlyStats[month - 1].hasWindData = false;
        }

        // Calculate temperature values
        if (temperatures.Size() > 0)
        {
            float mean = CalculateMean(temperatures);
            float stdDeviation = CalculateStdDeviation(temperatures, mean);

            monthlyStats[month - 1].avgTemperature = mean;
            monthlyStats[month - 1].temperatureStdDeviation = stdDeviation;
            monthlyStats[month - 1].hasTemperatureData = true;
        }
        else
        {
            monthlyStats[month - 1].avgTemperature = 0.0;
            monthlyStats[month - 1].temperatureStdDeviation = 0.0;
            monthlyStats[month - 1].hasTemperatureData = false;
        }

        // Calculate solar radiation values
        if (solarRadiation.Size() > 0)
        {
            float sumSolarRad = 0.0;

            for (int i = 0; i < solarRadiation.Size(); i++)
            {
                sumSolarRad += solarRadiation[i] / 6000;
            }
            monthlyStats[month - 1].totalSolarRad = sumSolarRad;
            monthlyStats[month - 1].hasSolarData = true;
        }
        else
        {
            monthlyStats[month - 1].totalSolarRad = 0.0;
            monthlyStats[month - 1].hasSolarData = false;
        }
        monthlyStats[month - 1].hasAnyData = monthlyStats[month - 1].hasWindData || monthlyStats[month - 1].hasTemperatureData || monthlyStats[month - 1].hasSolarData;
    }
    return true;
}
