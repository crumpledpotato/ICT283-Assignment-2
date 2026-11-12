#include "DataHelper.h"
#include "SortHelper.h"
#include "Date.h"

#include <iostream>

using namespace std;

namespace DataHelper
{
    void PrepareWeatherData(WeatherlogType& weather_data, std::map<int, BinarySearchTree<WeatherRecType>>& weatherMap)
    {
        cout << endl << "=== Sorting weather records ===" << endl << "." << endl << "." << endl << "." << endl;
        SortHelper::SortWeatherData(weather_data);
        cout << "Sorting completed" << endl;

        cout << endl << "=== Removing duplicated records ===" << endl << "." << endl << "." << endl << "." << endl;
        int duplicatesRemoved = SortHelper::RemoveDuplicates(weather_data);
        cout << "Duplicates removed : " << duplicatesRemoved << endl;

        BuildWeatherMap(weather_data, weatherMap);
    }

    void BuildWeatherMap( const WeatherlogType& weather_data,
                        map<int, BinarySearchTree<WeatherRecType>>& weatherMap)
    {
        int total = weather_data.Size();

        if (total == 0)
        {
            return;
        }
        int startIndex = 0;
        Date recordDate;
        int year;
        int nextYear;

        while (startIndex < total)
        {
            weather_data[startIndex].GetDate(recordDate);
            recordDate.GetYear(year);
            int endIndex = startIndex;

            while (endIndex + 1 < total)
            {
                weather_data[endIndex + 1].GetDate(recordDate);
                recordDate.GetYear(nextYear);

                if (nextYear != year)
                {
                    break;
                }
                endIndex++;
            }
            InsertBalanced(weather_data, weatherMap[year], startIndex, endIndex);
            startIndex = endIndex + 1;
        }
    }

    void InsertBalanced(const WeatherlogType& weather_data, BinarySearchTree<WeatherRecType>& tree, int left, int right)
    {
        if (left > right)
        {
            return;
        }
        int mid = left + (right - left) / 2;
        tree.Insert(weather_data[mid]);

        InsertBalanced(weather_data, tree, left, mid - 1);
        InsertBalanced(weather_data, tree, mid + 1, right);
    }
}
