#ifndef SORTHELPER_H
#define SORTHELPER_H

#include "WeatherRecType.h"
#include "Vector.h"

/**
 * @brief Handles sortation operations on the initial data store
 *
 * SortHelper is responsible for file handling processes, such as: <br>
 * - Holding a merge sort algorithm <br>
 * - Applying a merge sort on the initial data store <br>
 * - Skipping data entries that are duplicates of the existing stored data
 */
namespace SortHelper
{
    /**
     * @brief Merges two sorted sections of weather records.
     *
     * @param data Weather records being sorted.
     * @param temp Temporary storage for merging.
     * @param left Starting index.
     * @param mid Ending index of the left section.
     * @param right Ending index of the right section.
     */
    void Merge(WeatherlogType& data, WeatherlogType& temp, int left, int mid, int right);

    /**
     * @brief Recursively sorts weather records by Date and Time.
     *
     * @param data Weather records being sorted.
     * @param temp Temporary storage for merging.
     * @param left Starting index.
     * @param right Ending index.
     */
    void MergeSort(WeatherlogType& data, WeatherlogType& temp, int left, int right);

    /**
     * @brief Sorts weather records chronologically using Merge Sort.
     *
     * Uses WeatherRecType::operator< for comparisons
     *
     * @param data Weather records to sort.
     */
    void SortWeatherData(WeatherlogType& data);

    /**
     * @brief Removes duplicate weather records by timestamp.
     *
     * Assumes records have already been sorted chronologically <br>
     * Retains the first occurrence of each timestamp
     *
     * @param data Weather records to process.
     * @return Number of duplicate records removed.
     */
    int RemoveDuplicates(WeatherlogType& data);
}

#endif

