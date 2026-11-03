
#include "SortHelper.h"
#include "WeatherRecType.h"
#include "Vector.h"
#include "Date.h"
#include "Time.h"

#include <iostream>
#include <string>

using namespace std;

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

WeatherRecType MakeRecord(int day, int month, int year, int hour, int minute, int second,
                          float speed = 5.0f)
{
    Date date;
    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);

    Time time;
    time.SetHour(hour);
    time.SetMinute(minute);
    time.SetSecond(second);

    return WeatherRecType(date, time, speed, 25.0f, 100.0f);
}

bool IsSorted(const WeatherlogType& data)
{
    for (int i = 1; i < data.Size(); i++)
    {
        if (data[i] < data[i - 1])
        {
            return false;
        }
    }

    return true;
}

bool SameTimestamp(const WeatherRecType& a,
                   const WeatherRecType& b)
{
    return !(a < b) && !(b < a);
}

void TestEmptyVector()
{
    cout << endl << "=== Empty Vector Test ===" << endl;

    WeatherlogType data;

    SortHelper::SortWeatherData(data);

    Check(data.Size() == 0, "Empty vector remains empty");
    Check(IsSorted(data), "Empty vector is sorted");
}

void TestSingleRecord()
{
    cout << endl << "=== Single Record Test ===" << endl;

    WeatherlogType data;

    WeatherRecType record = MakeRecord(15, 6, 2015, 12, 30, 0);

    data.Insert(data.Size(), record);

    SortHelper::SortWeatherData(data);

    Check(data.Size() == 1, "Single record count unchanged");
    Check(SameTimestamp(data[0], record), "Single record preserved");
    Check(IsSorted(data), "Single record is sorted");
}

void TestAlreadySorted()
{
    cout << endl << "=== Already Sorted Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(1, 1, 2010, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2011, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2012, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2013, 0, 0, 0));

    SortHelper::SortWeatherData(data);

    Check(data.Size() == 4, "Already sorted count unchanged");
    Check(IsSorted(data), "Already sorted records remain sorted");
}

void TestReverseSorted()
{
    cout << endl << "=== Reverse Sorted Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(1, 1, 2021, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2016, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2012, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2010, 0, 0, 0));

    SortHelper::SortWeatherData(data);

    Check(data.Size() == 4, "Reverse sorted count unchanged");
    Check(IsSorted(data), "Reverse sorted records sorted correctly");

    Check(SameTimestamp(data[0],
          MakeRecord(1, 1, 2010, 0, 0, 0)),
          "Earliest year is first");

    Check(SameTimestamp(data[3],
          MakeRecord(1, 1, 2021, 0, 0, 0)),
          "Latest year is last");
}

void TestUnsortedRecords()
{
    cout << endl << "=== Unsorted Records Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(15, 6, 2015, 12, 0, 0));
    data.Insert(data.Size(), MakeRecord(10, 3, 2010, 8, 0, 0));
    data.Insert(data.Size(), MakeRecord(20, 9, 2021, 15, 0, 0));
    data.Insert(data.Size(), MakeRecord(5, 1, 2012, 10, 0, 0));
    data.Insert(data.Size(), MakeRecord(25, 12, 2016, 18, 0, 0));

    SortHelper::SortWeatherData(data);

    Check(data.Size() == 5, "Unsorted record count unchanged");
    Check(IsSorted(data), "Unsorted records sorted correctly");

    Check(SameTimestamp(data[0], MakeRecord(10, 3, 2010, 8, 0, 0)),
          "First record is 2010");

    Check(SameTimestamp(data[4],  MakeRecord(20, 9, 2021, 15, 0, 0)),
          "Last record is 2021");
}

void TestSameYear()
{
    cout << endl << "=== Same Year Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(20, 12, 2015, 12, 0, 0));
    data.Insert(data.Size(), MakeRecord(5, 1, 2015, 12, 0, 0));
    data.Insert(data.Size(), MakeRecord(10, 6, 2015, 12, 0, 0));

    SortHelper::SortWeatherData(data);

    Check(IsSorted(data), "Same year records sorted");

    Check(SameTimestamp(data[0], MakeRecord(5, 1, 2015, 12, 0, 0)),
          "January comes first");

    Check(SameTimestamp(data[2], MakeRecord(20, 12, 2015, 12, 0, 0)),
          "December comes last");
}

void TestSameDay()
{
    cout << endl << "=== Same Day Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(15, 6, 2015, 18, 30, 20));
    data.Insert(data.Size(), MakeRecord(15, 6, 2015, 8, 15, 10));
    data.Insert(data.Size(), MakeRecord(15, 6, 2015, 12, 45, 30));
    data.Insert(data.Size(), MakeRecord(15, 6, 2015, 8, 15, 5));

    SortHelper::SortWeatherData(data);

    Check(IsSorted(data), "Same day records sorted");

    Check(SameTimestamp(data[0], MakeRecord(15, 6, 2015, 8, 15, 5)),
          "Earliest second comes first");

    Check(SameTimestamp(data[3], MakeRecord(15, 6, 2015, 18, 30, 20)),
          "Latest time comes last");
}

void TestDuplicateTimestamps()
{
    cout << endl << "=== Duplicate Timestamp Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(1, 1, 2015, 10, 0, 0, 5.0f));
    data.Insert(data.Size(), MakeRecord(1, 1, 2010, 10, 0, 0, 8.0f));
    data.Insert(data.Size(), MakeRecord(1, 1, 2015, 10, 0, 0, 9.0f));
    data.Insert(data.Size(), MakeRecord(1, 1, 2021, 10, 0, 0, 6.0f));

    SortHelper::SortWeatherData(data);

    Check(data.Size() == 4, "Duplicates are not removed during sorting");
    Check(IsSorted(data), "Records with duplicates are sorted");

    Check(SameTimestamp(data[1], data[2]), "Duplicate timestamps remain adjacent");

    float speed1 = 0.0f;
    float speed2 = 0.0f;

    data[1].GetSpeed(speed1);
    data[2].GetSpeed(speed2);

    Check(speed1 == 5.0f && speed2 == 9.0f, "Equal timestamps preserve original relative order");
}

void TestRepeatedSorting()
{
    cout << endl << "=== Repeated Sorting Test ===" << endl;

    WeatherlogType data;

    data.Insert(data.Size(), MakeRecord(1, 1, 2021, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2010, 0, 0, 0));
    data.Insert(data.Size(), MakeRecord(1, 1, 2015, 0, 0, 0));

    SortHelper::SortWeatherData(data);
    SortHelper::SortWeatherData(data);

    Check(data.Size() == 3, "Repeated sorting preserves count");
    Check(IsSorted(data), "Repeated sorting remains correct");
}

void TestLargeDataset()
{
    cout << endl << "=== Large Dataset Test ===" << endl;

    WeatherlogType data;

    const int RECORD_COUNT = 10000;

    // Insert records in reverse chronological order.
    for (int i = RECORD_COUNT - 1; i >= 0; i--)
    {
        int year = 2010 + i / 365;
        int day = 1 + i % 28;
        int month = 1 + (i / 28) % 12;

        data.Insert(data.Size(),
                    MakeRecord(day, month, year, 12, 0, 0));
    }

    SortHelper::SortWeatherData(data);

    Check(data.Size() == RECORD_COUNT, "Large dataset count unchanged");

    Check(IsSorted(data), "Large dataset sorted correctly");
}

int main()
{
    cout << "======================================" << endl;
    cout << "        SORT HELPER UNIT TESTS        " << endl;
    cout << "======================================" << endl;

    TestEmptyVector();
    TestSingleRecord();
    TestAlreadySorted();
    TestReverseSorted();
    TestUnsortedRecords();
    TestSameYear();
    TestSameDay();
    TestDuplicateTimestamps();
    TestRepeatedSorting();
    TestLargeDataset();

    cout << endl;
    cout << "======================================" << endl;
    cout << "             TEST SUMMARY             " << endl;
    cout << "======================================" << endl;

    cout << "Tests passed: " << testsPassed << endl;
    cout << "Tests failed: " << testsFailed << endl;
    cout << "Total tests : " << testsPassed + testsFailed << endl;

    if (testsFailed == 0)
    {
        cout << "All SortHelper tests passed." << endl;
        return 0;
    }
    else
    {
        cout << "Some SortHelper tests failed." << endl;
        return 1;
    }
}
