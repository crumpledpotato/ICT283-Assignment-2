#include "FileHelper.h"
#include "MathHelper.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

bool FileHelper::SelectFile (string& filename, int& wastCol, int& speedCol, int& TCol, int& SRCol)
{
    cout << "Reading data_source.txt" << endl << ".\n.\n.\n" << endl;
    ifstream infile("data/data_source.txt");
    if (!infile)
    {
        cout << endl << ("Unable to open data_source.txt") << endl;
        return false;
    }
    getline(infile, filename);
    infile.close();

    filename = "data/" + filename;
    cout << "Data file : " << filename << endl;
    return FindColumn(filename, wastCol, speedCol, TCol, SRCol);
}

bool FileHelper::FindColumn (string filename, int& wastCol, int& speedCol, int& TCol, int& SRCol)
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

bool FileHelper::ReadData (string filename, int wastCol, int speedCol, int TCol, int SRCol, WeatherlogType& weather_data)
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

    // Read data row
    while (getline(infile, line))
    {
        string field;
        stringstream ss(line);
        int column = 0;
        string wast;
        string speed;
        string temperature;
        string solarRad;

        // Split rows
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

        // Validate if speed is a number
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
            cout << "WAST  : " << wast << endl;
            cout << " -- Record skipped --" << endl;
            cout << endl;
            continue;
        }

        // Split WAST into date and time
        int day;
        int month;
        int year;
        int hour;
        int minute;
        // int second;
        char separator;
        stringstream wastStream(wast);

        wastStream >> day;
        wastStream >> separator;
        wastStream >> month;
        wastStream >> separator;
        wastStream >> year;
        wastStream >> hour;
        wastStream >> separator;
        wastStream >> minute;

        Date date (day, month, year);
        Time time (hour, minute, 0);
        WeatherRecType record;

        record.SetDate(date);
        record.SetTime(time);
        record.SetSpeed(windSpeed);
        record.SetTemperature(temperatureValue);
        record.SetSolarRad(solarRadValue);

        if (!weather_data.Exists(record))
        {
            weather_data.Insert(weather_data.Size(), record);
        }
        else
        {
            cout << "Duplicate record skipped" << endl;
        }


        // Enable to print all records to terminal for testing
        /*cout << "Date  : " << date << endl;
        cout << "Time  : " << time << endl;
        cout << "Speed : " << windSpeed << "m/s" << endl << endl;*/
    }
    infile.close();
    return true;
}

bool FileHelper::WriteData (const WeatherlogType& weather_data)
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

    if (!MathHelper::TabulateStatistics(weather_data, inputYear, monthlyStats))
    {
        return false;
    }
    ofstream outfile("WindTempSolar.csv");
    if (!outfile)
    {
        cout << endl << "Error in creating WindTempSolar.csv" << endl;
        return false;
    }

    outfile << inputYear << endl;

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
                    outfile << monthlyStats[month - 1].avgWindSpeed << " (" << monthlyStats[month - 1].windStdDeviation << ")";
                }
                outfile << ",";
                if (monthlyStats[month - 1].hasTemperatureData)
                {
                    outfile << monthlyStats[month - 1].avgTemperature << " (" << monthlyStats[month - 1].temperatureStdDeviation << ")";
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
