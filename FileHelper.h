#ifndef FILEHELPER_H
#define FILEHELPER_H

/**
 * @author  Marcus
 * @version 4.0
 * @date    03/11/2026
 */

#include "Date.h"
#include "Time.h"
#include "Vector.h"
#include "WeatherRecType.h"

#include <string>

/**
 * @brief Handles file input, output, and file-related operations
 *
 * FileHelper is responsible for file handling processes, such as: <br>
 * - Selecting a file to read from a list of options <br>
 * - Reading the data and finding WAST and S columns <br>
 * - Displaying calculated statistics to the terminal <br>
 * - Writing output to file testoutput.csv
 */
namespace FileHelper
{
public:

    /**
     * @brief Allows the user to select an input CSV file
     *
     * Displays the available files and prompts user to input a validated choice <br>
     * Calls function FindColumn() to locate WAST, S, T, SR columns and displays the results
     *
     * @param filename Variable used to store the selected filename
     * @param wastCol Variable used to store the WAST column number
     * @param speedCol Variable used to store the S column number
     * @param TCol Variable used to store the T column number
     * @param SRCol Variable used to store the SR column number
     * @return true if a valid file and required columns are found, otherwise false
     */
    bool SelectFile (std::string& filename, int& wastCol, int& speedCol, int& TCol, int& SRCol);

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
    bool FindColumn (const std::string filename, int& wastCol, int& speedCol, int& TCol, int& SRCol);

     /**
     * @brief Reads wind data from a CSV file and stores data into WindRecType
     *
     * Reads the WAST date and time, S wind speed, T temperature and SR solar radiation from the selected columns <br>
     * Valid records are stored in weather_data <br>
     * Invalid or non-numeric wind speed values are skipped
     * If records match an existing stored record, record is also skipped
     *
     * @param filename Name of the CSV input file
     * @param wastCol Column number containing WAST data
     * @param speedCol Column number containing wind speed data
     * @param TCol Column number containing temperature data
     * @param SRCol Column number containing solar radiation data
     * @param weather_data The stored weather records
     * @return true if the file is successfully opened and read, otherwise false
     */
    bool ReadData (const std::string filename, int wastCol, int speedCol, int TCol, int SRCol, WeatherlogType& weather_data);

    /**
     * @brief Displays the main program menu and gets the user's selection.
     *
     * @return The selected menu option.
     */
    int Menu();

    /**
     * @brief Displays the menu and processes the user's selection.
     *
     * Loops the menu until the user selects the exit option.
     *
     * @param weather_data The stored weather records.
     */
     void ProcessMenu(WeatherlogType& weather_data);

    /**
     * @brief Writes weather data to a .csv file
     *
     * Creates or overwrites WindTempSolar.csv <br>
     * Prompts user to input a year <br>
     * Writes the monthly statistics to WindTempSolar.csv
     *
     * @param weather_data The stored weather records
     * @return true if the file is successfully written, otherwise false
     */
    bool WriteData (const WeatherlogType& weather_data);
};
#endif
