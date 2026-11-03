#include "Vector.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int passed = 0;
int failed = 0;

void Check(bool condition, const char* testName)
{
    if (condition)
    {
        cout << "[PASS] " << testName << endl;
        passed++;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        failed++;
    }
}

// Test 1: Default constructor
void TestDefaultConstructor()
{
    Vector<int> numbers;
    Check(numbers.Size() == 0, "Default constructor");
}

// Tests 2, 3, 4: Parameterised constructor
void TestParameterisedConstructor()
{
    Vector<int> numbers(5);
    Check(numbers.Size() == 5, "Parameterised constructor");

    Vector<int> empty(0);
    Check(empty.Size() == 0, "Zero-size constructor");

    bool exceptionThrown = false;
    try
    {
        Vector<int> invalid(-5);
    }
    catch (const invalid_argument&)
    {
        exceptionThrown = true;
    }

    Check(exceptionThrown, "Negative-size constructor");
}

// Tests 5, 6, 8: Insert
void TestInsert()
{
    Vector<int> numbers;
    Check(numbers.Insert(0, 10), "Insert into empty Vector");
    Check(numbers.Insert(0, 5), "Insert at beginning");

    Check(numbers.Size() == 2 && numbers[0] == 5 &&
          numbers[1] == 10, "Beginning insertion shifts elements");

    Check(numbers.Insert(2, 20), "Insert at end");
    Check(numbers.Size() == 3 && numbers[2] == 20, "End insertion");
}

// Test 10: Remove
void TestRemove()
{
    Vector<int> numbers;

    numbers.Insert(0, 10);
    numbers.Insert(1, 20);
    numbers.Insert(2, 30);
    numbers.Insert(3, 40);
    numbers.Insert(4, 50);

    Check(numbers.Remove(0), "Remove first element");
    Check(numbers.Size() == 4 && numbers[0] == 20, "First removal shifts elements");

    Check(numbers.Remove(1), "Remove middle element");
    Check(numbers.Size() == 3 && numbers[1] == 40, "Middle removal");

    Check(numbers.Remove(2), "Remove last element");
    Check(numbers.Size() == 2 && numbers[1] == 40, "Last removal");
}

// Test 11: Invalid removal
void TestInvalidRemove()
{
    Vector<int> numbers;

    numbers.Insert(0, 10);
    Check(!numbers.Remove(-1), "Negative removal position");
    Check(!numbers.Remove(1), "Removal beyond size");
    Check(numbers.Size() == 1, "Invalid removal preserves size");
}

// Tests 12, 13: Indexing
void TestIndexing()
{
    Vector<int> numbers(3);

    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;

    Check(numbers[1] == 20, "Read using operator[]");
    numbers[1] = 99;
    Check(numbers[1] == 99, "Update using operator[]");

    const Vector<int>& constantNumbers = numbers;
    Check(constantNumbers[2] == 30, "Const operator[]");
}

// Test 16: Automatic resizing
void TestResize()
{
    Vector<int> numbers(1);

    numbers[0] = 100;

    for (int i = 1; i < 250; i++)
    {
        numbers.Insert(numbers.Size(), i);
    }

    Check(numbers.Size() == 250, "Automatic resizing updates size");
    bool correct = true;

    for (int i = 1; i < numbers.Size(); i++)
    {
        if (numbers[i] != i)
        {
            correct = false;
        }
    }

    Check(correct && numbers[0] == 100, "Automatic resizing preserves values");
}

// Test 17: Copy constructor
void TestCopyConstructor()
{
    Vector<int> original;

    original.Insert(0, 10);
    original.Insert(1, 20);
    original.Insert(2, 30);

    Vector<int> copied(original);
    Check(copied.Size() == 3, "Copy constructor size");

    Check(copied[0] == 10 && copied[1] == 20 &&
          copied[2] == 30, "Copy constructor values");

    original[0] = 99;
    Check(copied[0] == 10, "Copy constructor deep copy");
}

// Test 18: Assignment operator
void TestAssignment()
{
    Vector<int> original;

    original.Insert(0, 10);
    original.Insert(1, 20);
    original.Insert(2, 30);

    Vector<int> assigned;
    assigned = original;
    Check(assigned.Size() == 3, "Assignment operator size");

    Check(assigned[0] == 10 && assigned[1] == 20 &&
          assigned[2] == 30, "Assignment operator values");

    original[0] = 99;
    Check(assigned[0] == 10, "Assignment operator deep copy");
}

// Test 19: Self-assignment
void TestSelfAssignment()
{
    Vector<int> numbers;

    numbers.Insert(0, 10);
    numbers.Insert(1, 20);

    numbers = numbers;

    Check(numbers.Size() == 2 && numbers[0] == 10 &&
          numbers[1] == 20, "Self-assignment");
}

// Test 20: Empty Vector copying
void TestEmptyCopy()
{
    Vector<int> empty;
    Vector<int> copied(empty);
    Check(copied.Size() == 0, "Copy empty Vector");

    Vector<int> assigned;
    assigned.Insert(0, 50);
    assigned = empty;
    Check(assigned.Size() == 0, "Assign empty Vector");
}

int main()
{
    cout << "====================================" << endl;
    cout << "          VECTOR UNIT TESTS         " << endl;
    cout << "====================================" << endl;

    TestDefaultConstructor();
    TestParameterisedConstructor();
    TestInsert();
    TestRemove();
    TestInvalidRemove();
    TestIndexing();
    TestResize();
    TestCopyConstructor();
    TestAssignment();
    TestSelfAssignment();
    TestEmptyCopy();

    cout << endl;
    cout << "====================================" << endl;
    cout << "              SUMMARY               " << endl;
    cout << "====================================" << endl;

    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "Total: " << passed + failed << endl;

    if (failed == 0)
    {
        cout << "ALL TESTS PASSED" << endl;
        return 0;
    }
    else
    {
        cout << "SOME TESTS FAILED" << endl;
        return 1;
    }
}
