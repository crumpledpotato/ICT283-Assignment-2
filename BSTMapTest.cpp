#include "Date.h"
#include "Time.h"
#include "WeatherRecType.h"
#include "Vector.h"
#include "BST.h"
#include "FileHelper.h"
#include "DataHelper.h"

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>

using namespace std;

// ========================================
// Test counters
// ========================================

int testsPassed = 0;
int testsFailed = 0;

void Check(bool condition, const string& testName)
{
    if (condition)
    {
        cout << "[PASS] " << testName << endl;
        testsPassed++;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        testsFailed++;
    }
}

// ========================================
// Helper: Create weather record
// ========================================

WeatherRecType MakeRecord(int day, int month, int year, int hour, int minute, int second,
    float speed = 5.0f, float temperature = 25.0f, float solarRad = 100.0f)
{
    Date date;
    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);

    Time time;
    time.SetHour(hour);
    time.SetMinute(minute);
    time.SetSecond(second);

    return WeatherRecType(date, time, speed, temperature, solarRad);
}

// ========================================
// TEST 1: Date and Time
// ========================================

void TestDateTime()
{
    cout << "\n===== TEST 1: DATE AND TIME =====\n";

    WeatherRecType record = MakeRecord(15, 6, 2015, 10, 30, 45);

    Date date;
    Time time;

    record.GetDate(date);
    record.GetTime(time);

    int day = 0, month = 0, year = 0;
    int hour = 0, minute = 0, second = 0;

    date.GetDay(day);
    date.GetMonth(month);
    date.GetYear(year);

    time.GetHour(hour);
    time.GetMinute(minute);
    time.GetSecond(second);

    Check(day == 15, "Day extraction");
    Check(month == 6, "Month extraction");
    Check(year == 2015, "Year extraction");

    Check(hour == 10, "Hour extraction");
    Check(minute == 30, "Minute extraction");
    Check(second == 45, "Second extraction");
}

// ========================================
// TEST 2: WeatherRecType comparisons
// ========================================

void TestWeatherComparison()
{
    cout << "\n===== TEST 2: WEATHER COMPARISON =====\n";

    WeatherRecType early = MakeRecord(1, 1, 2015, 10, 0, 0);
    WeatherRecType late = MakeRecord(1, 1, 2015, 11, 0, 0);
    WeatherRecType previousYear = MakeRecord(31, 12, 2014, 23, 59, 59);
    WeatherRecType sameTime = MakeRecord(1, 1, 2015, 10, 0, 0, 20.0f, 30.0f, 200.0f);

    Check(early < late, "Earlier hour is smaller");
    Check(!(late < early), "Later hour is not smaller");
    Check(previousYear < early, "Previous year is smaller");
    Check(early == sameTime, "Same timestamp is equal");
    Check(!(early < sameTime) && !(sameTime < early), "Same timestamp is equivalent for BST");

    WeatherRecType nextDay = MakeRecord(2, 1, 2015, 0, 0, 0);
    WeatherRecType nextMonth = MakeRecord(1, 2, 2015, 0, 0, 0);

    Check(early < nextDay, "Day ordering");
    Check(nextDay < nextMonth, "Month ordering");

    WeatherRecType nextMinute = MakeRecord(1, 1, 2015, 10, 1, 0);
    WeatherRecType nextSecond = MakeRecord(1, 1, 2015, 10, 0, 1);

    Check(early < nextMinute, "Minute ordering");
    Check(early < nextSecond, "Second ordering");
}

// ========================================
// TEST 3: BST operations
// ========================================

// Traversal callback required by BST.
void PrintInteger(int& value)
{
    cout << value << " ";
}

void TestBST()
{
    cout << "\n===== TEST 3: BST OPERATIONS =====\n";

    BinarySearchTree<int> tree;

    Check(tree.IsValid(), "Empty BST is valid");

    Check(tree.Insert(50), "Insert root 50");
    Check(tree.Insert(30), "Insert left child 30");
    Check(tree.Insert(70), "Insert right child 70");
    Check(tree.Insert(20), "Insert 20");
    Check(tree.Insert(40), "Insert 40");
    Check(tree.Insert(60), "Insert 60");
    Check(tree.Insert(80), "Insert 80");

    Check(!tree.Insert(30), "Reject duplicate 30");

    Check(tree.Search(50), "Search root");
    Check(tree.Search(20), "Search leaf");
    Check(!tree.Search(99), "Search missing value");

    Check(tree.IsValid(), "BST remains valid");

    cout << "InOrder expected: 20 30 40 50 60 70 80\n";
    cout << "InOrder actual:   ";
    tree.InOrder(PrintInteger);
    cout << endl;

    cout << "PreOrder expected: 50 30 20 40 70 60 80\n";
    cout << "PreOrder actual:   ";
    tree.PreOrder(PrintInteger);
    cout << endl;

    cout << "PostOrder expected: 20 40 30 60 80 70 50\n";
    cout << "PostOrder actual:   ";
    tree.PostOrder(PrintInteger);
    cout << endl;

    BinarySearchTree<int> copied(tree);

    Check(copied.Search(40), "Copy constructor");
    Check(copied.IsValid(), "Copied BST is valid");

    BinarySearchTree<int> assigned;
    assigned = tree;

    Check(assigned.Search(70), "Copy assignment");
    Check(assigned.IsValid(), "Assigned BST is valid");

    tree.DeleteTree();

    Check(!tree.Search(50), "Deleted tree contains no old records");
    Check(tree.IsValid(), "Deleted BST remains valid");
}

// ========================================
// TEST 4: BST weather record duplicates
// ========================================

void TestWeatherBST()
{
    cout << "\n===== TEST 04: WEATHER BST =====\n";

    BinarySearchTree<WeatherRecType> tree;

    WeatherRecType record1 = MakeRecord(1, 1, 2015, 10, 0, 0);
    WeatherRecType record2 = MakeRecord(1, 1, 2015, 11, 0, 0);
    WeatherRecType duplicate =  MakeRecord(1, 1, 2015, 10, 0, 0, 99.0f, 99.0f, 99.0f);

    Check(tree.Insert(record1), "Insert first weather record");
    Check(tree.Insert(record2), "Insert second weather record");

    Check(!tree.Insert(duplicate), "Reject duplicate timestamp");
    Check(tree.Search(record1), "Search weather record");
    Check(tree.IsValid(), "Weather BST is valid");
}

// ========================================
// TEST 5: Map year grouping
// ========================================

void TestYearMap()
{
    cout << "\n===== TEST 5: MAP YEAR GROUPING =====\n";

    WeatherlogType records;

    records.Insert(records.Size(), MakeRecord(1, 1, 2010, 10, 0, 0));
    records.Insert(records.Size(), MakeRecord(1, 1, 2011, 10, 0, 0));
    records.Insert(records.Size(), MakeRecord(2, 1, 2011, 10, 0, 0));
    records.Insert(records.Size(), MakeRecord(1, 1, 2015, 10, 0, 0));
    records.Insert(records.Size(), MakeRecord(1, 1, 2021, 10, 0, 0));

    map<int, BinarySearchTree<WeatherRecType>> weatherMap;

    for (int i = 0; i < records.Size(); i++)
    {
        Date date;
        records[i].GetDate(date);

        int year = 0;
        date.GetYear(year);

        weatherMap[year].Insert(records[i]);
    }

    Check(records.Size() == 5, "Five records created");

    Check(weatherMap.size() == 4, "Four unique years");

    Check(weatherMap.count(2010) == 1, "Year 2010 exists");
    Check(weatherMap.count(2011) == 1, "Year 2011 exists");
    Check(weatherMap.count(2015) == 1, "Year 2015 exists");
    Check(weatherMap.count(2021) == 1, "Year 2021 exists");
    Check(weatherMap.count(2012) == 0, "Year 2012 absent");

    Check(weatherMap.at(2011).IsValid(), "2011 BST is valid");
}

// ========================================
// TEST 6: Vector operations
// ========================================

void TestVector()
{
    cout << "\n===== TEST 6: VECTOR =====\n";

    Vector<int> numbers;

    Check(numbers.Size() == 0, "Initially empty");

    numbers.Insert(0, 10);
    numbers.Insert(1, 20);
    numbers.Insert(2, 30);

    Check(numbers.Size() == 3, "Three elements inserted");

    Check(numbers[0] == 10, "First element");
    Check(numbers[1] == 20, "Second element");

    numbers.Insert(1, 15);

    Check(numbers.Size() == 4, "Insertion increases size");
    Check(numbers[1] == 15, "Insert shifts elements");
    Check(numbers[2] == 20, "Original element shifted");

    numbers[0] = 99;
    Check(numbers[0] == 99, "Index assignment");
}

// ========================================
// TEST 7: Real CSV year distribution
// ========================================

void TestCSVYearDistribution()
{
    cout << "\n===== TEST 7: CSV YEAR DISTRIBUTION =====\n";

    WeatherlogType weather_data;

    ifstream infile("data/data_source.txt");

    if (!infile)
    {
        cout << "Cannot open data_source.txt\n";
        return;
    }

    string filename;
    int wastCol = 0;
    int speedCol = 0;
    int TCol = 0;
    int SRCol = 0;

    while (getline(infile, filename))
    {
        if (filename.empty())
        {
            continue;
        }

        filename = "data/" + filename;

        if (FileHelper::FindColumn(
            filename, wastCol, speedCol, TCol, SRCol))
        {
            FileHelper::ReadData(filename, wastCol, speedCol, TCol, SRCol, weather_data);
        }
    }

    map<int, int> yearCounts;

    for (int i = 0; i < weather_data.Size(); i++)
    {
        Date date;
        weather_data[i].GetDate(date);

        int year = 0;
        date.GetYear(year);

        yearCounts[year]++;
    }

    int total = 0;

    for (const auto& entry : yearCounts)
    {
        cout << "Year " << entry.first
             << ": " << entry.second
             << " records\n";

        total += entry.second;
    }

    Check(total == weather_data.Size(), "Year counts matches total records");

    Check(yearCounts.size() >= 4, "At least four years loaded");

    cout << "Total loaded: " << weather_data.Size() << endl;
}

// ========================================
// Main test runner
// ========================================

int main()
{
    cout << "====================================\n";
    cout << "         OVERALL UNIT TESTS\n";
    cout << "====================================\n";

    TestDateTime();
    TestWeatherComparison();
    TestBST();
    TestWeatherBST();
    TestYearMap();
    TestVector();

    cout << "\n====================================\n";
    cout << "             TEST SUMMARY\n";
    cout << "====================================\n";

    cout << "Passed: " << testsPassed << endl;
    cout << "Failed: " << testsFailed << endl;

    if (testsFailed == 0)
    {
        cout << "RESULT: ALL EXECUTED TESTS PASSED\n";
    }
    else
    {
        cout << "RESULT: SOME TESTS FAILED\n";
    }


    cout << endl << "====================================\n";
    cout << "       FULL BST CONSTRUCT TEST\n";
    cout << "====================================\n";
    WeatherlogType weather_data;
    map<int, BinarySearchTree<WeatherRecType>> weatherMap;

    // Test insertion of all CSV
    ifstream infile("data/data_source.txt");
    if (!infile)
    {
        cout << "Unable to open data_source.txt" << endl;
        return 1;
    }

    string filename;
    int wastCol;
    int speedCol;
    int TCol;
    int SRCol;

    while (getline(infile, filename))
    {
        if (filename.empty())
        {
            continue;
        }
        filename = "data/" + filename;
        cout << endl << "Reading data file : " << filename << endl;

        if (FileHelper::FindColumn(filename, wastCol, speedCol, TCol, SRCol))
        {
            if (!FileHelper::ReadData(filename, wastCol, speedCol, TCol, SRCol, weather_data))
            {
                cout << "Unable to read " << filename << endl;
            }
        }
        else
        {
            cout << "Unable to find required columns in " << filename << endl;
        }
    }
    infile.close();

    DataHelper::PrepareWeatherData(weather_data, weatherMap);

    cout << "\n===== BST Validation =====" << endl;

    int totalBSTRecords = 0;

    map<int, BinarySearchTree<WeatherRecType>>::iterator counter = weatherMap.begin();

    for (int i = 0; i < weatherMap.size(); i++)
    {
        int year = counter->first;
        int count = counter->second.Size();
        bool valid = counter->second.IsValid();

        cout << "Year : " << year << " | Records : " << right << setw(6) << count << " | BST valid : " << valid << endl;

        totalBSTRecords += count;
        counter++;
    }
    cout << endl << "Total BST records : " << totalBSTRecords << endl;
    cout << "Total Vector records : " << weather_data.Size() << endl;
    cout << "Number of years loaded : " << weatherMap.size() << endl;
    cout << "Number of valid records : " << weather_data.Size() << endl;

    cout << endl << "If TOTAL BST, TOTAL VECTOR and VALID RECORDS match, all valid data is successfully inserted" << endl;
    cout << "If all BST Valid = 1, each year's BST satisfies the BST Representation Invariant" << endl;

    cout << endl << "====================================\n";
    cout << "         TESTING CONCLUDED\n";
    cout << "====================================\n";
    if (testsFailed == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
