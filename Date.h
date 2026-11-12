#ifndef DATE_H
#define DATE_H

/**
 * @author  Marcus
 * @version 1.0
 * @date 28/10/2026
 */

#include <string>

/** @class Date
 * @brief Stores a calendar date object
 * @details The Date class stores the day, month and year of a date.
 *          The month is validated to determine if it falls within the range 1 to 12. <br>
 *          A valid month number is converted to its respective month name. <br>
 * @details If the month is out of bounds, The numeric month value is displayed instead.
 */
class Date
{
public:
    /** @brief Default constructor
     * Creates a Date object with day, month and year set to 0
     */
    Date();

    /** @brief Parameterised constructor that initialises all attributes
     * @param day The day of the date
     * @param month The month of the date
     * @param year The year of the date
     */
    Date(int day, int month, int year);

    /** @brief Retrieves the day of the date
     * @param day Reference used to return the day
     */
    void GetDay(int & day) const;

    /** @brief Retrieves the month of the date
     * @param month Reference used to return the month
     */
    void GetMonth(int & month) const;

    /** @brief Retrieves the year of the date
     * @param year Reference used to return the year
     */
    void GetYear(int & year) const;

    /** @brief Sets the day of the date
     * @param day The day of the date
     */
    void SetDay(int day);

    /** @brief Sets the month of the date
     * @param month The month of the date
     */
    void SetMonth(int month);

    /** @brief Sets the year of the date
     * @param year The year of the date
     */
    void SetYear(int year);

    /** @brief Retrieves the name of the month as a word
     * @param monthName Reference used to return the month name
     */
    void GetMonthName (std::string& monthName) const;

private:

    /**
     * @brief Day of the date
     */
    int m_day;

    /**
     * @brief Month of the date
     */
    int m_month;

    /**
     * @brief Year of the date
     */
    int m_year;
};

/**
 * @brief Compares two dates chronologically.
 * @param lhs The first date.
 * @param rhs The second date.
 * @return true if lhs is earlier than rhs.
 */
bool operator<(const Date& lhs, const Date& rhs);

/**
 * @brief Compares two dates to identify duplicates.
 * @param lhs The first date.
 * @param rhs The second date.
 * @return true if lhs and rhs are the same.
 */
bool operator==(const Date& lhs, const Date& rhs);

#endif
