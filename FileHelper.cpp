#include "FileHelper.h"
#include "MathHelper.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

namespace FileHelper
{
    bool FindColumn (const string& filename, int& wastCol, int& speedCol, int& TCol, int& SRCol)
    {
        // Open CSV file
        ifstream infile(filename);

        if (!infile)
        {
            cout << endl << "Error in opening " << filename;
            return false;
        }
        else
        {
            cout << endl << "Successfully opened " << filename << endl;
        }
        // Read header line
        string line;
        getline(infile, line);

        // Split header into attributes
        string field;
        stringstream ss(line);

        int column = 0;
        wastCol = -1;
        speedCol = -1;
        TCol = -1;
        SRCol = -1;

        // Find column index for WAST and Speed
        while (getline(ss, field, ','))
        {
            // cout << "Column " << column+1 << " : " << field << endl;
            if (field == "WAST")
            {
                wastCol = column;
            }
            if (field == "S")
            {
                speedCol = column;
            }
            if (field == "T")
            {
                TCol = column;
            }
            if (field == "SR")
            {
                SRCol = column;
            }
            column++;
        }
        infile.close();
        cout << endl << "WAST Column  : " << wastCol+1 << endl;
        cout << "Speed Column : " << speedCol+1 << endl;
        cout << "T Column     : " << TCol+1 << endl;
        cout << "SR Column    : " << SRCol+1 << endl << endl;

        // Ensure all columns were found
        if (wastCol == -1 || speedCol == -1 || TCol == -1 || SRCol == -1)
        {
            return false;
        }
        return true;
    }

    bool ReadData(const string& filename, int wastCol, int speedCol, int TCol, int SRCol, WeatherlogType& weather_data)
    {
        ifstream infile(filename);
        if (!infile)
        {
            cout << endl << "Error in opening " << filename << endl;
            return false;
        }
        // Skip header row
        string line;
        getline(infile, line);

        int skippedCount = 0;
        int loadedCount = 0;

        // Read data row
        while (getline(infile, line))
        {
            WeatherRecType record;

            if (!ParseRecord(line, wastCol, speedCol, TCol, SRCol, record))
            {
                skippedCount++;
                continue;
            }

            /*if (RecordExists(weather_data, record))
            {
                cout << endl << "Duplicate record found - skipped" << endl;
                continue;
            }*/
            weather_data.Insert(weather_data.Size(), record);
            loadedCount++;
        }
        infile.close();
        cout << "File            : " << filename << endl;
        cout << "Records loaded  : " << loadedCount << endl;
        cout << "Records skipped : " << skippedCount << endl;
        cout << "==============================================================" << endl;
        return true;
    }

    bool WriteData (const map<int, BinarySearchTree<WeatherRecType>>& weatherMap)
    {
        int inputYear;
        bool hasYearData = false;

        cout << endl << "Enter a year to search  : ";
        while (!(cin >> inputYear) || inputYear < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input, please enter a valid year : ";
        }

        MonthlyStats monthlyStats[12];

        if (!MathHelper::TabulateStatistics(weatherMap, inputYear, monthlyStats))
        {
            return false;
        }

        ofstream outfile("WindTempSolar.csv");
        if (!outfile)
        {
            cout << endl << "Error in creating WindTempSolar.csv" << endl;
            return false;
        }
        outfile << fixed << setprecision(1);
        outfile << inputYear << endl;
        outfile << "Month,\"Average Wind Speed(stdev, mad)\"," << "\"Average Ambient Temperature(stdev, mad)\"," << "Total Solar Radiation" << endl;

        for (int month = 1; month <= 12; month++)
        {
            if (monthlyStats[month - 1].hasAnyData)
                {
                    hasYearData = true;

                    Date date(1, month, inputYear);
                    string monthName;
                    date.GetMonthName(monthName);

                    outfile << monthName << ",";

                    if (monthlyStats[month - 1].hasWindData)
                    {
                        outfile << "\"" << monthlyStats[month - 1].avgWindSpeed << " (" << monthlyStats[month - 1].windStdDeviation << ", "
                        << monthlyStats[month - 1].windMAD << ")\"";
                    }
                    outfile << ",";
                    if (monthlyStats[month - 1].hasTemperatureData)
                    {
                        outfile << "\"" << monthlyStats[month - 1].avgTemperature << " (" << monthlyStats[month - 1].temperatureStdDeviation << ", "
                        << monthlyStats[month - 1].temperatureMAD << ")\"";
                    }
                    outfile << ",";
                    if (monthlyStats[month - 1].hasSolarData)
                    {
                        outfile << monthlyStats[month - 1].totalSolarRad;
                    }
                    outfile << endl;
                }
        }

        if (!hasYearData)
        {
            outfile << "No Data" << endl;
        }
        outfile.close();
        cout << endl << "WindTempSolar.csv created successfully for year " << inputYear << endl;
        return true;
    }

    bool ParseDateTime(const std::string& wast, Date& date, Time& time)
    {
        int day;
        int month;
        int year;
        int hour;
        int minute;

        char separator1;
        char separator2;
        char separator3;

        stringstream wastStream(wast);
        if (!(wastStream >> day >> separator1 >> month >> separator2 >> year
                >> hour >> separator3 >> minute))
        {
            return false;
        }

        if (separator1 != '/' || separator2 != '/' || separator3 != ':')
        {
            return false;
        }

        if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31 ||
            hour < 0 || hour > 23 || minute < 0 || minute > 59)
        {
            return false;
        }

        date = Date(day, month, year);
        time = Time(hour, minute, 0);
        return true;
    }

    bool ParseRecord(const std::string& line, int wastCol, int speedCol, int TCol, int SRCol, WeatherRecType& record)
    {
        string field;
        string wast;
        string speed;
        string temperature;
        string solarRad;

        stringstream ss(line);
        int column = 0;

        while (getline(ss, field, ','))
        {
            if (column == wastCol)
            {
                wast = field;
            }

            if (column == speedCol)
            {
                speed = field;
            }

            if (column == TCol)
            {
                temperature = field;
            }

            if (column == SRCol)
            {
                solarRad = field;
            }

            column++;
        }

        float windSpeed;
        float temperatureValue;
        float solarRadValue;

        try
        {
            windSpeed = stof(speed);
            temperatureValue = stof(temperature);
            solarRadValue = stof(solarRad);
        }
        catch (const invalid_argument& e)
        {
            return false;
        }
        catch (const out_of_range& e)
        {
            return false;
        }

        Date date;
        Time time;

        if (!ParseDateTime(wast, date, time))
        {
            return false;
        }

        record.SetDate(date);
        record.SetTime(time);
        record.SetSpeed(windSpeed);
        record.SetTemperature(temperatureValue);
        record.SetSolarRad(solarRadValue);

        return true;
    }

    bool RecordExists(const WeatherlogType& weather_data, const WeatherRecType& record)
    {
        for (int i = 0; i < weather_data.Size(); i++)
        {
            if (weather_data[i] == record)
            {
                return true;
            }
        }
        return false;
    }
}
