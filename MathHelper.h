#ifndef MATHHELPER_H
#define MATHHELPER_H

/**
 * @author  Marcus
 * @version 3.0
 * @date    07/10/2026
 */

#include "WeatherRecType.h"

/**
 * @brief Stores calculated statistics record for a month's data
 *
 * MonthlyStats contains the calculated statistics for wind speed, temperature and solar radiation data for a month's duration
 */
struct MonthlyStats
{
    float avgWindSpeed = 0.0f;
    float windStdDeviation = 0.0f;
    float avgTemperature = 0.0f;
    float temperatureStdDeviation = 0.0f;
    float totalSolarRad = 0.0f;

    bool hasWindData = false;
    bool hasTemperatureData = false;
    bool hasSolarData = false;
    bool hasAnyData = false;
};

/**
 * @brief Performs mathematical calculations on wind data
 *
 * MathHelper calculates the averages and sample standard deviation of weather data
 */
class MathHelper
{
public:

    /**
     * @brief Calculates the mean of a set of values
     *
     * @param values The Vector containing the values
     * @return The mean of the values, or 0 if the Vector is empty
     */
    float CalculateMean (const Vector<float>& values);

    /**
     * @brief Calculates the standard deviation of a set of values
     *
     * @param values The Vector containing the values
     * @param mean The mean of the values
     * @return The sample standard deviation, or 0 if there is less than 2 values
     */
    float CalculateStdDeviation (const Vector<float>& values, float mean);

    /**
     * @brief Calculates wind speed statistics for a selected month and year
     *
     * Calculates the average wind speed and sample standard deviation for a user-selected month and year <br>
     * The results are then displayed to the terminal
     *
     * @param weather_data The stored weather records
     * @return True when statistics are successfully calculated, otherwise false
     */
    bool CalculateWindStats(const WeatherlogType& weather_data);

    /**
     * @brief Calculates temperature statistics for a selected year
     *
     * Calculates the average temperature and sample standard deviation sorted by month for the selected year <br>
     * The results are then displayed to the terminal
     *
     * @param weather_data The stored weather records
     * @return True when statistics are successfully calculated, otherwise false
     */
    bool CalculateTemperatureStats(const WeatherlogType& weather_data);

    /**
     * @brief Calculates total solar radiation each month for a selected year
     *
     * Calculates the total solar radiation in kWh/m2, sorted by month for the selected year <br>
     * The results are then displayed to the terminal
     *
     * @param weather_data The stored weather records
     * @return True when statistics are successfully calculated, otherwise false
     */
    bool CalculateSolarRad(const WeatherlogType& weather_data);

    /**
     * @brief Calculates monthly wind, temperature and solar statistics for a selected year
     *
     * Calculates the following statistics, sorted by month for the selected year:<br>
     * - Average wind speed <br>
     * - Wind speed standard deviation <br>
     * - Average ambient air temperature <br>
     * - Temperature standard deviation <br>
     * - Total solar radiation <br>
     *
     * Months with blank data fields or missing data fields entirely will be skipped <br>
     * The results are then passed to FileHelper.cpp for export functions <br>
     * The results will not be displayed on the terminal
     *
     * @param weather_data The stored weather records
     * @param inputYear The year selected for statistical calculations
     * @param monthlyStats Array storing statistics for each month
     * @return True when statistics are successfully calculated, otherwise false
     */
    bool TabulateStatistics(const WeatherlogType& weather_data, int inputYear, MonthlyStats monthlyStats[]);
};

#endif
