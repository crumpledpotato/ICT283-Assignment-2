#ifndef TIME_H
#define TIME_H

/**
 * @author  Marcus
 * @version 2.0
 * @date 07/10/2026
 */

using namespace std;


/** @class Time
 * @brief Stores a 24 hour time object
 * @details The Time class stores the hour, minute, second of a time. <br>
 *          The hour is validated to be between 0 and 23.<br>
 *          The minute and second are validated to be between 0 and 59. <br>
 * @details Invalid input for these values will be discarded and set to 0.<br>
 */
class Time
{
public:
    /** @brief Default constructor
     * Creates a Time object with hour, minute and second set to 0
     */
    Time();

    /** @brief Parameterised constructor that initialises all attributes
     * @param hour The hour of the time
     * @param minute The minute of the time
     * @param second The second of the time
     */
    Time(int hour, int minute, int second);

    /** @brief Retrieves the hour of the time
     * @param hour Reference used to return the hour
     */
    void GetHour(int& hour) const;

    /** @brief Retrieves the minute of the time
     * @param minute Reference used to return the minute
     */
    void GetMinute(int& minute) const;

    /** @brief Retrieves the second of the time
     * @param time Reference used to return the second
     */
    void GetSecond(int& second) const;

    /** @brief Sets the hour of the time
     * @param hour The hour of the time
     */
    void SetHour(int hour);

    /** @brief Sets the minute of the time
     * @param minute The minute of the time
     */
    void SetMinute(int minute);

    /** @brief Sets the second of the time
     * @param second The second of the time
     */
    void SetSecond(int second);

private:

    /**
     * @brief Hour of the time
     */
    int m_hour;

    /**
     * @brief Minute of the time
     */
    int m_minute;

    /**
     * @brief Second of the time
     */
    int m_second;
};
#endif
