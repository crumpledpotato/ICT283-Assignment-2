#ifndef FILEHELPER_H
#define FILEHELPER_H

/**
 * @author  Marcus
 * @version 4.0
 * @date    13/11/2026
 */

#include "Date.h"
#include "Time.h"
#include "Vector.h"
#include "WeatherRecType.h"
#include "BST.h"

#include <string>
#include <map>

/**
 * @brief Handles file input, output, and file-related operations
 *
 * FileHelper is responsible for file handling processes, such as: <br>
 * - Reading the data and finding WAST, S, T & SR columns <br>
 * - Parsing to organise necessary data fields <br>
 * - Displaying calculated statistics to the terminal <br>
 * - Writing output to file testoutput.csv
 */
namespace FileHelper
{
    /**
     * @brief Finds the WAST and S columns in the CSV file
     *
     * Searches the header row for the WAST and S field names and stores the indexes
     *
     * @param filename Name of the CSV input file
     * @param wastCol Variable used to store the WAST column number
     * @param speedCol Variable used to store the S column number
     * @param TCol Variable used to store the T column number
     * @param SRCol Variable used to store the SR column number
     * @return true if both columns are found, otherwise false
     */
    bool FindColumn (const std::string& filename, int& wastCol, int& speedCol, int& TCol, int& SRCol);

     /**
     * @brief Reads weather data from a CSV file and stores data into WeatherLogType
     *
     * Reads the WAST date and time, S wind speed, T temperature and SR solar radiation from the selected columns <br>
     * Valid records are stored in weather_data <br>
     * Invalid or non-numeric wind speed values are skipped
     * If records match an existing stored record, record is also skipped
     *
     * @param filename Name of the CSV input file
     * @param wastCol Column index containing WAST data
     * @param speedCol Column index containing wind speed data
     * @param TCol Column index containing temperature data
     * @param SRCol Column index containing solar radiation data
     * @param weather_data The stored weather records
     * @return true if the file is successfully opened and read, otherwise false
     */
    bool ReadData (const std::string& filename, int wastCol, int speedCol, int TCol, int SRCol, WeatherlogType& weather_data);

    /**
     * @brief Writes weather data to a .csv file
     *
     * Creates or overwrites WindTempSolar.csv <br>
     * Prompts user to input a year <br>
     * Writes the monthly statistics to WindTempSolar.csv
     *
     * @param weatherMap Map containing yearly weather BSTs
     * @return true if the file is successfully written, otherwise false
     */
    bool WriteData (const map<int, BinarySearchTree<WeatherRecType>>& weatherMap);

    /**
     * @brief Parses WAST data into Date and Time objects
     *
     * Extracts the day, month, year, hour and minute from a WAST string. <br>
     * Validates the date and time format and checks that values are within the accepted ranges. <br>
     * Stores the parsed values in the provided Date and Time objects.
     *
     * @param wast String containing the WAST date and time
     * @param date Date object used to store the parsed date
     * @param time Time object used to store the parsed time
     * @return true if the date and time are successfully parsed, otherwise false
     */
    bool ParseDateTime(const std::string& wast, Date& date, Time& time);

    /**
     * @brief Parses a CSV row into a WeatherRecType record
     *
     * Extracts WAST, wind speed, temperature and solar radiation values
     * from their corresponding CSV columns. <br>
     * Converts numeric strings into float values and validates the data. <br>
     * Calls ParseDateTime() to extract the date and time. <br>
     * Stores the parsed values in the provided WeatherRecType object.
     *
     * @param line String containing one CSV data row
     * @param wastCol Column index containing WAST data
     * @param speedCol Column index containing wind speed data
     * @param TCol Column index containing temperature data
     * @param SRCol Column index containing solar radiation data
     * @param record WeatherRecType object used to store the parsed record
     * @return true if the record is successfully parsed, otherwise false
     */
    bool ParseRecord(const std::string& line, int wastCol, int speedCol, int TCol, int SRCol, WeatherRecType& record);
}
#endif
