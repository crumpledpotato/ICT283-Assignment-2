#include "MathHelper.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    Vector<float> values;

    cout << "Inserting 10, 20, 30 respectively" << endl << endl;
    values.Insert(0, 10.0f);
    values.Insert(1, 20.0f);
    values.Insert(2, 30.0f);

    float mean = MathHelper::CalculateMean(values);
    float stdDeviation = MathHelper::CalculateStdDeviation(values, mean);

    cout << "Test 1: CalculateMean" << endl;
    cout << "Expected: 20" << endl;
    cout << "Actual: " << mean << endl;

    if (fabs(mean - 20.0f) < 0.001f)
    {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }

    cout << endl << "Test 2: CalculateStdDeviation" << endl;
    cout << "Expected: 10" << endl;
    cout << "Actual: " << stdDeviation << endl;

    if (fabs(stdDeviation - 10.0f) < 0.001f)
    {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }

    return 0;
}
