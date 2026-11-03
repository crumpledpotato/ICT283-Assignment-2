#include <iostream>
#include <string>

using namespace std;

// Named constants for menu options
const int WIND_STATS = 1;
const int TEMPERATURE_STATS = 2;
const int SOLAR_STATS = 3;
const int EXPORT_STATS = 4;
const int EXIT_PROGRAM = 5;

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

int main()
{
    string filename;

    int wastCol;
    int speedCol;
    int TCol;
    int SRCol;

    WeatherlogType weather_data;

    if (FileHelper::SelectFile(filename, wastCol, speedCol, TCol, SRCol))
    {
        if (FileHelper::ReadData(filename, wastCol, speedCol, TCol, SRCol, weather_data))
        {
            cout << "Number of valid records : " << weather_data.Size() << endl;
            ProcessMenu(weather_data);
        }
        else
        {
            cout << endl << "Unable to read weather data" << endl;
        }
    }
    else
    {
        cout << endl << "Unale to find the required data files or columns" << endl;
    }
    return 0;
}


int Menu()
{
    int option;

    cout << endl << "=============== Wind Data Analysis ===============" << endl;
    cout << "1. Average wind speed and standard deviation" << endl;
    cout << "2. Average ambient temperature and standard deviation" << endl;
    cout << "3. Total solar radiation" << endl;
    cout << "4. Export wind, temperature and solar statistics" << endl;
    cout << "5. Exit" << endl;
    cout << "==================================================" << endl << endl;
    cout << "Enter your option : ";

    while (!(cin >> option))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Invalid input, please enter a number from the menu : ";
    }
    return option;
}

void ProcessMenu(const WeatherlogType& weather_data)
{
    int option;

    do
    {
        option = Menu();
        switch (option)
        {
        case WIND_STATS:
            MathHelper::CalculateWindStats(weather_data); break;
        case TEMPERATURE_STATS:
            MathHelper::CalculateTemperatureStats(weather_data); break;
        case SOLAR_STATS:
            MathHelper::CalculateSolarRad(weather_data); break;
        case EXPORT_STATS:
            FileHelper::WriteData(weather_data); break;
        case EXIT_PROGRAM:
            cout << endl << "===== Exiting the programme =====" << endl; break;
        default:
            cout << endl << "Invalid option, please enter a number from the menu" << endl;
        }
    }
    while (option != EXIT_PROGRAM);
}
