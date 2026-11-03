#include "SortHelper.h"

namespace SortHelper
{
    void Merge(WeatherlogType& data, WeatherlogType& temp, int left, int mid, int right)
    {
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right)
        {
            if (data[j] < data[i])
            {
                temp[k] = data[j];
                j++;
            }
            k++;
        }

        while (i <= mid)
        {
            temp[k] = data[i];
            i++;
            k++;
        }

        while (j <= right)
        {
            temp[k] = data[j];
            j++;
            k++;
        }

        for (int index = left; index <= right; index++)
        {
            data[index] = temp[index];
        }
    }

    void MergeSort(WeatherlogType& data, WeatherlogType& temp, int left, int right)
    {
       if (left >= right)
       {
           return;
       }

       int mid = left + (right - left) / 2;
       MergeSort(data, temp, left, mid);
       MergeSort(data, temp, mid + 1, right);

       Merge(data, temp, left, mid, right);
    }

    void SortWeatherData(WeatherlogType& data)
    {
        if (data.Size() < 2)
        {
            return;
        }
        WeatherlogType temp;

        for (int i = 0; i < data.Size(); i++)
        {
            temp.Insert(temp.Size(), WeatherRecType());
        }
        MergeSort(data, temp, 0, data.Size() - 1);
    }
}
