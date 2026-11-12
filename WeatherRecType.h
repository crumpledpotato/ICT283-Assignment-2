#ifndef WEATHERTYPE_H
#define WEATHERTYPE_H

/**
 * @author  Marcus
 * @version 1.0
 * @date    07/10/2026
 */

#include "Date.h"
#include "Time.h"
#include "Vector.h"

/**
 * @brief Represents one weather observation
 *
 * WeatherType stores the date, time, wind speed, ambient temperature and solar radiation recorded for one weather observation <br>
 * The class provides constructors, getters and setters to access and modify the weather data
 */
class WeatherRecType
{
public:

    /**
     * @brief Default constructor
     *
     * Initialises the weather record with default values
     */
    WeatherRecType();

    /**
     * @brief Parameterised constructor
     *
     * Initialises a weather record using the supplied date, time, wind speed, temperature and solar radiation values
     *
     * @param date The date of the weather observation
     * @param time The time of the weather observation
     * @param speed The wind speed in metres per second
     * @param temperature The ambient temperature in degrees Celsius
     * @param solarRad The solar radiation in watts per square metre.
     */
    WeatherRecType(const Date& date, const Time& time, float speed, float temperature, float solarRad);

    /**
     * @brief Gets the date of the weather observation
     *
     * @param date Reference variable used to return the date
     */
    void GetDate(Date& date) const;

    /**
     * @brief Gets the time of the weather observation
     *
     * @param time Reference variable used to return the time
     */
    void GetTime(Time& time) const;

    /**
     * @brief Gets the wind speed of the weather observation
     *
     * @param speed Reference variable used to return the wind speed
     */
    void GetSpeed(float& speed) const;

    /**
     * @brief Gets the temperature of the weather observation
     *
     * @param temperature Reference variable used to return the temperature
     */
    void GetTemperature(float& temperature) const;

    /**
     * @brief Gets the solar radiation measurement of the weather observation
     *
     * @param solarRad Reference variable used to return the solar radiation measurement
     */
    void GetSolarRad(float& solarRad) const;

    /**
     * @brief Sets the date of the weather observation
     *
     * @param date The new date of the weather observation
     */
    void SetDate(const Date& date);

    /**
     * @brief Sets the time of the weather observation
     *
     * @param time The new time of the weather observation
     */
    void SetTime(const Time& time);

    /**
     * @brief Sets the wind speed of the weather observation
     *
     * @param speed The new wind speed of the weather observation
     */
    void SetSpeed(float speed);

    /**
     * @brief Sets the temperature of the weather observation
     *
     * @param temperature The new temperature of the weather observation
     */
    void SetTemperature(float temperature);

    /**
     * @brief Sets the solar radiation measurement of the weather observation
     *
     * @param solarRad The new solar radiation measurement of the weather observation
     */
    void SetSolarRad(float solarRad);

    /**
     * @brief Compares 2 weather records to evaluate if it matches
     *
     * Compares date and time to validate if this record matches another record in any field
     *
     * @param other The weather record to compare
     * @return true if both fields match, false if any field does not match
     */
    bool operator==(const WeatherRecType& other) const;

    /**
     * @brief Compares 2 weather records to compare
     *
     * Compares date and time to evaluate which comes first chronologically, based on the year, month, day, hour, min <br>
     * Used by the BinarySearchTree to maintain chronological ordering and prevent duplication in timestamps
     *
     * @param other The weather record to compare
     * @return true if this record occurs before the other record, otherwise false
     */
    bool operator<(const WeatherRecType& other) const;

private:

    /**
     * @brief Date of the weather observation
     */
    Date m_date;

    /**
     * @brief Time of the weather observation
     */
    Time m_time;

    /**
     * @brief Wind speed of the weather observation
     */
    float m_speed;

    /**
     * @brief Temperature of the weather observation
     */
    float m_temperature;

    /**
     * @brief Solar radiation measurement of the weather observation
     */
    float m_solarRad;
};

typedef Vector<WeatherRecType> WeatherlogType;

#endif
