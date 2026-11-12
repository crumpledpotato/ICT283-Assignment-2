#include <iostream>
#include "Date.h"
#include "Time.h"
#include "WeatherRecType.h"

using namespace std;

int main()
{
    cout << "WeatherRecType Unit Test" << endl;
    cout << "========================" << endl << endl;

    // Test 1 - Default Constructor

    cout << "Test 1 - Default Constructor" << endl;
    cout << "----------------------------" << endl;

    WeatherRecType record1;

    Date date;
    Time time;
    float speed;
    float temperature;
    float solarRad;

    record1.GetDate(date);
    record1.GetTime(time);
    record1.GetSpeed(speed);
    record1.GetTemperature(temperature);
    record1.GetSolarRad(solarRad);

    cout << "Date        : " << date << endl;
    cout << "Time        : " << time << endl;
    cout << "Wind speed  : " << speed << " m/s" << endl;
    cout << "Temperature : " << temperature << " degrees C" << endl;
    cout << "Solar Rad   : " << solarRad << " W/m2" << endl << endl;

    // Test 2 - Parameterised Constructor
    // ==================================

    cout << "Test 2 - Parameterised Constructor" << endl;
    cout << "----------------------------------" << endl;

    Date testDate(5, 10, 2026);
    Time testTime(10, 30, 0);

    WeatherRecType record2(testDate, testTime, 789.123, 25.5, 450.75);

    record2.GetDate(date);
    record2.GetTime(time);
    record2.GetSpeed(speed);
    record2.GetTemperature(temperature);
    record2.GetSolarRad(solarRad);

    cout << "Date        : " << date << endl;
    cout << "Time        : " << time << endl;
    cout << "Wind speed  : " << speed << " m/s" << endl;
    cout << "Temperature : " << temperature << " degrees C" << endl;
    cout << "Solar Rad   : " << solarRad << " W/m2" << endl << endl;

    // Test 3 - Setters
    // ================

    cout << "Test 3 - Setters" << endl;
    cout << "----------------" << endl;

    Date newDate(15, 11, 2026);
    Time newTime(14, 45, 30);

    record1.SetDate(newDate);
    record1.SetTime(newTime);
    record1.SetSpeed(12.5);
    record1.SetTemperature(28.3);
    record1.SetSolarRad(800.0);

    record1.GetDate(date);
    record1.GetTime(time);
    record1.GetSpeed(speed);
    record1.GetTemperature(temperature);
    record1.GetSolarRad(solarRad);

    cout << "Date        : " << date << endl;
    cout << "Time        : " << time << endl;
    cout << "Wind speed  : " << speed << " m/s" << endl;
    cout << "Temperature : " << temperature << " degrees C" << endl;
    cout << "Solar Rad   : " << solarRad << " W/m2" << endl << endl;

    // Test 4 - Invalid Date and Time
    // ==============================

    cout << "Test 4 - Invalid Date and Time" << endl;
    cout << "------------------------------" << endl;

    Date invalidDate(20, 20, 2020);
    Time invalidTime(30, 100, 100);

    record1.SetDate(invalidDate);
    record1.SetTime(invalidTime);

    record1.GetDate(date);
    record1.GetTime(time);

    cout << "Invalid Date : " << date << endl;
    cout << "Invalid Time : " << time << endl;

    // Test 5 - Getters
    // ================

    cout << endl;
    cout << "Test 5 - Getters" << endl;
    cout << "----------------" << endl;

    Date getterDate(25, 12, 2026);
    Time getterTime(18, 20, 15);

    record1.SetDate(getterDate);
    record1.SetTime(getterTime);
    record1.SetSpeed(20.75);
    record1.SetTemperature(31.2);
    record1.SetSolarRad(950.5);

    record1.GetDate(date);
    record1.GetTime(time);
    record1.GetSpeed(speed);
    record1.GetTemperature(temperature);
    record1.GetSolarRad(solarRad);

    cout << "Date        : " << date << endl;
    cout << "Time        : " << time << endl;
    cout << "Wind speed  : " << speed << " m/s" << endl;
    cout << "Temperature : " << temperature << " degrees C" << endl;
    cout << "Solar Rad   : " << solarRad << " W/m2" << endl << endl;

    // Test 6 - WeatherlogType / Vector
    // ================================

    cout << "Test 6 - WeatherlogType" << endl;
    cout << "-----------------------" << endl;

    WeatherlogType weather_data;

    WeatherRecType record3(
        Date(5, 10, 2026),
        Time(10, 30, 0),
        789.123,
        25.5,
        450.75
    );

    WeatherRecType record4(
        Date(6, 10, 2026),
        Time(11, 40, 0),
        12.5,
        26.8,
        600.25
    );

    weather_data.Insert(weather_data.Size(), record3);
    weather_data.Insert(weather_data.Size(), record4);

    cout << "Number of records : " << weather_data.Size() << endl << endl;

    for (int i = 0; i < weather_data.Size(); i++)
    {
        Date recordDate;
        Time recordTime;
        float recordSpeed;
        float recordTemperature;
        float recordSolarRad;

        weather_data[i].GetDate(recordDate);
        weather_data[i].GetTime(recordTime);
        weather_data[i].GetSpeed(recordSpeed);
        weather_data[i].GetTemperature(recordTemperature);
        weather_data[i].GetSolarRad(recordSolarRad);

        cout << "Record " << i + 1 << endl;
        cout << "Date        : " << recordDate << endl;
        cout << "Time        : " << recordTime << endl;
        cout << "Wind speed  : " << recordSpeed << " m/s" << endl;
        cout << "Temperature : " << recordTemperature << " degrees C" << endl;
        cout << "Solar Rad   : " << recordSolarRad << " W/m2" << endl;
        cout << endl;
    }

    cout << "===============" << endl;
    cout << "Tests Completed" << endl;
    cout << "===============" << endl;
    return 0;
}
