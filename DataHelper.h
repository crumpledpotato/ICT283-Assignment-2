#ifndef DATAHELPER_H
#define DATAHELPER_H

#include "WeatherRecType.h"
#include "Vector.h"
#include "BST.h"

#include <map>

namespace DataHelper
{
    /**
     * @brief Prepares weather records for analysis.
     *
     * Sorts weather records chronologically, removes duplicate timestamps <br>
     * Builds the yearly weather map
     *
     * @param weather_data Collection of weather records.
     * @param weatherMap Map containing yearly BSTs.
     */
    void PrepareWeatherData(WeatherlogType& weather_data, std::map<int, BinarySearchTree<WeatherRecType>>& weatherMap);

    /**
     * @brief Organises weather records by year.
     *
     * Extracts the year from each weather record and creates the corresponding entry in the weather map
     *
     * Currently creates year entries only <br>
     * Balanced BST insertion will be implemented later
     *
     * @param weather_data Collection of weather records.
     * @param weatherMap Map containing yearly BSTs.
     */
    void BuildWeatherMap( const WeatherlogType& weather_data, std::map<int, BinarySearchTree<WeatherRecType>>& weatherMap);

    /**
     * @brief Inserts sorted weather records into a BST using midpoint-first insertion.
     *
     * @param weather_data Chronologically sorted weather records.
     * @param tree BST receiving the records.
     * @param left Starting index of the range.
     * @param right Ending index of the range.
     */
    void InsertBalanced(const WeatherlogType& weather_data, BinarySearchTree<WeatherRecType>& tree, int left, int right);
}
#endif
