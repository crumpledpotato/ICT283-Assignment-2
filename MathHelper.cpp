#include "MathHelper.h"
#include "Date.h"
#include "Time.h"
#include "WeatherRecType.h"

#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @struct PearsonSums
 * @brief Stores accumulated values for Pearson correlation calculations.
 *
 * Maintains the number of paired observations and the sums required to calculate the sample Pearson Correlation Coefficient (sPCC) <br>
 * Values are accumulated directly during BST traversal without storing individual observations in a Vector
 */
struct PearsonSums
{
    int count = 0;
    double sumX = 0.0;
    double sumY = 0.0;
    double sumX2 = 0.0;
    double sumY2 = 0.0;
    double sumXY = 0.0;

    /**
     * @brief Adds a pair of observations to the accumulated statistics.
     *
     * Updates the observation count, individual sums, squared sums, and the sum of the products of the two variables.
     *
     * @param x First observation value.
     * @param y Second observation value.
     */
    void Add(double x, double y)
    {
        count++;
        sumX += x;
        sumY += y;
        sumX2 += x * x;
        sumY2 += y * y;
        sumXY += x * y;
    }

    /**
     * @brief Calculates the sample Pearson Correlation Coefficient (sPCC).
     *
     * Uses the accumulated sums to calculate the linear correlation between two variables <br>
     * Returns false when fewer than two observations exist or when either variable has zero variance.
     *
     * @param result Reference used to store the calculated coefficient.
     * @return true if the correlation is calculated successfully, false if the coefficient is undefined.
     */
    bool Calculate(double& result) const
    {
        if (count < 2)
        {
            return false;
        }
        double numerator = (count * sumXY) - (sumX * sumY);
        double varX = (count * sumX2) - (sumX * sumX);
        double varY = (count * sumY2) - (sumY * sumY);

        if (varX <= 0.0 || varY <= 0.0)
        {
            return false;
        }
        result = numerator / sqrt(varX * varY);
        return true;
    }
};

/**
 * @struct SPCCData
 * @brief Stores the selected month and three Pearson accumulators.
 *
 * Maintains separate accumulated statistics for the following : <br>
 * S_T: Wind speed and temperature <br>
 * S_R: Wind speed and solar radiation <br>
 * T_R: Temperature and solar radiation <br>
 *
 * Used during BST traversal to calculate all three correlations without creating additional Vectors.
 */
struct SPCCData
{
    int selectedMonth = 0;
    PearsonSums ST;
    PearsonSums SR;
    PearsonSums TR;
};

// initalise struct of structs of SPCC
static SPCCData spccData;

/**
 * @brief Processes a weather record during BST traversal.
 *
 * Checks whether the record belongs to the selected month <br>
 * If it matches, extracts wind speed, temperature and solar radiation, then updates the three Pearson accumulators.
 *
 * @param record Reference to the weather record being processed.
 */
void ProcessSPCCRecord(const WeatherRecType& record)
{
    Date date;
    int month;
    record.GetDate(date);
    date.GetMonth(month);

    if (month != spccData.selectedMonth)
    {
        return;
    }

    float speed;
    record.GetSpeed(speed);
    float temperature;
    record.GetTemperature(temperature);
    float solarRad;
    record.GetSolarRad(solarRad);

    spccData.ST.Add(speed, temperature);
    spccData.SR.Add(speed, solarRad);
    spccData.TR.Add(temperature, solarRad);
}

namespace MathHelper
{

    float CalculateMean (const Vector<float>& values)
    {
        float total = 0.0;
        if (values.Size() == 0)
        {
            return 0.0;
        }

        for (int i = 0; i < values.Size(); i++)
        {
            total += values[i];
        }
        return total / values.Size();

    }

    float CalculateStdDeviation (const Vector<float>& values, float mean)
    {
        if (values.Size() < 2)
        {
            return 0.0;
        }
        float squaredDifferenceSum = 0.0;

        for (int i = 0; i < values.Size(); i++)
        {
            float difference = values[i] - mean;
            squaredDifferenceSum += difference * difference;
        }
        return sqrt(squaredDifferenceSum / (values.Size()-1));
    }


    static int selectedMonth;
    static Vector<float>* selectedWindSpeeds = nullptr;

    /**
     *@brief Collect wind speeds for the selected month
     *@param record Weather recprd visited during BST traversal
     */
    static void CollectWindSpeed(const WeatherRecType& record)
    {
        Date date;
        int recordMonth;
        float speed;

        record.GetDate(date);
        date.GetMonth(recordMonth);

        if (recordMonth == selectedMonth)
        {
            record.GetSpeed(speed);
            selectedWindSpeeds->Insert(selectedWindSpeeds->Size(), speed);
        }
    }

    bool CalculateWindStats(const map<int, BinarySearchTree<WeatherRecType>>& weatherMap)
    {
        int inputMonth;
        int inputYear;
        Vector<float> windSpeeds;

        cout << endl << "Enter a month to search : ";
        while (!(cin >> inputMonth) || inputMonth < 1 || inputMonth > 12)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input, please enter a number between 1 to 12 : ";
        }
        cout << endl << "Enter a year to search  : ";
        while (!(cin >> inputYear) || inputYear < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input, please enter a valid year : ";
        }

        // Search for BST records for the selected year
        map<int, BinarySearchTree<WeatherRecType>>::const_iterator counter;
        counter = weatherMap.find(inputYear);

        if (counter == weatherMap.end())
        {
            cout << endl << "No matching records for " << inputMonth << " / " << inputYear << " found" << endl;
            return false;
        }
        selectedMonth = inputMonth;
        selectedWindSpeeds = &windSpeeds;
        counter->second.InOrder(CollectWindSpeed);
        selectedWindSpeeds = nullptr;

        if (windSpeeds.Size() == 0)
        {
            cout << endl << "No matching records for " << inputMonth << " / " << inputYear << " found" << endl;
            return false;
        }
        float mean = CalculateMean(windSpeeds);
        float stdDeviation = CalculateStdDeviation(windSpeeds, mean);

        Date selectedDate(1, inputMonth, inputYear);
        string monthName;
        selectedDate.GetMonthName(monthName);

        cout << endl << "==================================================" << endl;
        cout << "                    STATISTICS" << endl;
        cout << "==================================================" << endl;
        cout << monthName << " " << inputYear << " : " << endl;
        cout << fixed << setprecision(1);
        cout << endl << "Average speed      : " << (mean * 3.6) << "km/h" << endl;
        cout << "Sample stdeviation : " << (stdDeviation * 3.6) << "km/h" << endl << endl;
        return true;
    }

    /*bool CalculateTemperatureStats(const map<int, BinarySearchTree<WeatherRecType>>& weatherMap)
    {
        int inputYear;
        cout << endl << "Enter a year to search  : ";
        while (!(cin >> inputYear) || inputYear < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input, please enter a valid year : ";
        }

        cout << endl << "==================================================" << endl;
        cout << "              TEMPERATURE STATISTICS" << endl;
        cout << "==================================================" << endl;
        cout << endl << inputYear << endl << endl;

        cout << fixed << setprecision(1);

        Vector<float> monthlyTemperatures[12];
        Date date;
        float temperature;
        int recordMonth;
        int recordYear;

        for (int i =0; i < weather_data.Size(); i++)
        {
            const WeatherRecType& record = weather_data[i];

            record.GetDate(date);
            record.GetTemperature(temperature);
            date.GetMonth(recordMonth);
            date.GetYear(recordYear);

            if (recordYear == inputYear && recordMonth >= 1 && recordMonth <= 12)
            {
                monthlyTemperatures[recordMonth-1].Insert(
                    monthlyTemperatures[recordMonth - 1].Size(), temperature);
            }
        }

        for (int month = 1; month <= 12; month++)
        {
            Date selectedDate (1, month, inputYear);
            string monthName;
            selectedDate.GetMonthName(monthName);

            if (monthlyTemperatures[month - 1].Size() > 0)
            {
                float mean = CalculateMean(monthlyTemperatures[month - 1]);
                float stdDeviation = CalculateStdDeviation(monthlyTemperatures[month - 1], mean);
                cout << left << setw(10) << monthName << " : " << mean << " degrees C," << "\t stdev : " << stdDeviation << endl;
            }
            else
            {
                cout << left << setw(10) << monthName << " : No Data" << endl;
            }
        }
        return true;
    }*/

    bool CalculateSolarRad(const WeatherlogType& weather_data)
    {
        int inputYear;
        cout << endl << "Enter a year to search  : ";
        while (!(cin >> inputYear) || inputYear < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input, please enter a valid year : ";
        }

        cout << endl << "==================================================" << endl;
        cout << "            SOLAR RADIATION STATISTICS" << endl;
        cout << "==================================================" << endl;
        cout << endl << inputYear << endl << endl;

        cout << fixed << setprecision(1);
        for (int month = 1; month <= 12 ; month++)
        {
            float totalSolar = 0.0;
            WeatherRecType record;
            Date date;
            float solarRad;
            int recordMonth;
            int recordYear;
            for (int i = 0; i < weather_data.Size(); i++)
            {
                record = weather_data[i];
                record.GetDate(date);
                record.GetSolarRad(solarRad);

                date.GetMonth(recordMonth);
                date.GetYear(recordYear);

                if (recordMonth == month && recordYear == inputYear)
                {
                    // Condition stated in Assignment brief
                    if (solarRad >= 100)
                    {
                        totalSolar += solarRad / 6000;
                    }
                }
            }
            Date selectedDate (1, month, inputYear);
            string monthName;
            selectedDate.GetMonthName(monthName);

            if (totalSolar > 0)
            {
                cout << left << setw(10) << monthName << " : "<< totalSolar << " kWh/m2" << endl;
            }
            else
            {
                cout << left << setw(10) << monthName << " : No Data" << endl;
            }
        }
         return true;
    }

    bool TabulateStatistics(const WeatherlogType& weather_data, int inputYear, MonthlyStats monthlyStats[])
    {
        for (int month = 1; month <= 12; month++)
        {
            Vector<float> windSpeeds;
            Vector<float> temperatures;
            Vector<float> solarRadiation;

            for (int i = 0; i < weather_data.Size(); i++)
            {
                WeatherRecType record = weather_data[i];

                Date date;
                float speed;
                float temperature;
                float solarRad;

                int recordMonth;
                int recordYear;

                record.GetDate(date);
                record.GetSpeed(speed);
                record.GetTemperature(temperature);
                record.GetSolarRad(solarRad);

                date.GetMonth(recordMonth);
                date.GetYear(recordYear);

                if (recordMonth == month && recordYear == inputYear)
                {
                    windSpeeds.Insert(windSpeeds.Size(), speed);
                    temperatures.Insert(temperatures.Size(), temperature);

                    if (solarRad >= 100)
                    {
                        solarRadiation.Insert(solarRadiation.Size(), solarRad);
                    }
                }
            }

            // Calculate wind values
            if (windSpeeds.Size() > 0)
            {
                float mean = CalculateMean(windSpeeds);
                float stdDeviation = CalculateStdDeviation(windSpeeds, mean);

                monthlyStats[month - 1].avgWindSpeed = mean * 3.6;
                monthlyStats[month - 1].windStdDeviation = stdDeviation * 3.6;
                monthlyStats[month - 1].hasWindData = true;
            }
            else
            {
                monthlyStats[month - 1].avgWindSpeed = 0.0;
                monthlyStats[month - 1].windStdDeviation = 0.0;
                monthlyStats[month - 1].hasWindData = false;
            }

            // Calculate temperature values
            if (temperatures.Size() > 0)
            {
                float mean = CalculateMean(temperatures);
                float stdDeviation = CalculateStdDeviation(temperatures, mean);

                monthlyStats[month - 1].avgTemperature = mean;
                monthlyStats[month - 1].temperatureStdDeviation = stdDeviation;
                monthlyStats[month - 1].hasTemperatureData = true;
            }
            else
            {
                monthlyStats[month - 1].avgTemperature = 0.0;
                monthlyStats[month - 1].temperatureStdDeviation = 0.0;
                monthlyStats[month - 1].hasTemperatureData = false;
            }

            // Calculate solar radiation values
            if (solarRadiation.Size() > 0)
            {
                float sumSolarRad = 0.0;

                for (int i = 0; i < solarRadiation.Size(); i++)
                {
                    sumSolarRad += solarRadiation[i] / 6000;
                }
                monthlyStats[month - 1].totalSolarRad = sumSolarRad;
                monthlyStats[month - 1].hasSolarData = true;
            }
            else
            {
                monthlyStats[month - 1].totalSolarRad = 0.0;
                monthlyStats[month - 1].hasSolarData = false;
            }
            monthlyStats[month - 1].hasAnyData = monthlyStats[month - 1].hasWindData || monthlyStats[month - 1].hasTemperatureData || monthlyStats[month - 1].hasSolarData;
        }
        return true;
    }

    struct SPCCResult
    {
        double ST = 0.0;
        double SR = 0.0;
        double TR = 0.0;

        bool validST = false;
        bool validSR = false;
        bool validTR = false;
    };

    bool CalculateSPCC(const map<int, BinarySearchTree<WeatherRecType>>& weatherMap, int inputMonth, SPCCResult& result)
    {
        result = SPCCResult();

        if (inputMonth < 1 || inputMonth > 12)
        {
            return false;
        }

        spccData = SPCCData();
        spccData.selectedMonth = inputMonth;
        map<int, BinarySearchTree<WeatherRecType>>::const_iterator counter;

        for (counter = weatherMap.begin(); counter != weatherMap.end(); counter++)
        {
            counter->second.InOrder(ProcessSPCCRecord);
        }

        result.validST = spccData.ST.Calculate(result.ST);
        result.validSR = spccData.SR.Calculate(result.SR);
        result.validTR = spccData.TR.Calculate(result.TR);

        return result.validSR || result.validST || result.validTR;
    }

    void PrintSPCC(const map<int, BinarySearchTree<WeatherRecType>>& weatherMap)
    {
        int inputMonth;
        cout << endl << "Enter a month to search (1-12) : ";
        while (!(cin >> inputMonth) || inputMonth < 1 || inputMonth > 12)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, please enter a month between 1 to 12 : ";
        }
        SPCCResult result;
        CalculateSPCC(weatherMap, inputMonth, result);

        Date selectedDate(1, inputMonth, 1);
        string monthName;
        selectedDate.GetMonthName(monthName);

        cout << endl << "========================================" << endl;
        cout << "       PEARSON CORRELATION (sPCC)" << endl;
        cout << "========================================" << endl;

        cout << "Sample Pearson Correlation Coefficient for " << monthName << endl;
        cout << fixed << setprecision(2);

        cout << "S_T : ";
        if (result.validST)
        {
            cout << result.ST << endl;
        }
        else
        {
            cout << "Undefined" << endl;
        }

        cout << "S_R : ";
        if (result.validSR)
        {
            cout << result.SR << endl;
        }
        else
        {
            cout << "Undefined" << endl;
        }

        cout << "T_R : ";
        if (result.validTR)
        {
            cout << result.TR << endl;
        }
        else
        {
            cout << "Undefined" << endl;
        }
    }
}
