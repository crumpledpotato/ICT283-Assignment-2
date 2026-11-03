
#include "BST.h"
#include <iostream>

using namespace std;

int passed = 0;
int failed = 0;

int traversal[100];
int traversalCount = 0;

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

void CollectValue(int& value)
{
    if (traversalCount < 100)
    {
        traversal[traversalCount] = value;
        traversalCount++;
    }
}

void ResetTraversal()
{
    traversalCount = 0;
}

bool CheckTraversal(const int expected[], int count)
{
    if (traversalCount != count)
    {
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        if (traversal[i] != expected[i])
        {
            return false;
        }
    }

    return true;
}

void FillTree(BinarySearchTree<int>& tree)
{
    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(20);
    tree.Insert(40);
    tree.Insert(60);
    tree.Insert(80);
}

// Test 1: Default constructor
void TestConstructor()
{
    BinarySearchTree<int> tree;

    Check(!tree.Search(10), "Default constructor creates empty tree");
    Check(tree.IsValid(), "Empty tree is valid");
}

// Test 2: Insertion
void TestInsert()
{
    BinarySearchTree<int> tree;

    Check(tree.Insert(50), "Insert root node");
    Check(tree.Insert(30), "Insert left child");
    Check(tree.Insert(70), "Insert right child");

    Check(tree.Search(50) && tree.Search(30) &&
          tree.Search(70), "Inserted values are stored correctly");
}

// Test 3: Duplicate insertion
void TestDuplicate()
{
    BinarySearchTree<int> tree;

    tree.Insert(50);
    Check(!tree.Insert(50), "Reject duplicate root");

    tree.Insert(30);
    Check(!tree.Insert(30), "Reject duplicate child");

    ResetTraversal();
    tree.InOrder(CollectValue);

    Check(traversalCount == 2, "Duplicate insertion does not increase node count");
}

// Tests 4-5: Search
void TestSearch()
{
    BinarySearchTree<int> tree;
    FillTree(tree);

    Check(tree.Search(50), "Search root");
    Check(tree.Search(20), "Search left subtree");
    Check(tree.Search(80), "Search right subtree");

    Check(!tree.Search(100), "Search missing value");
    Check(!tree.Search(-10), "Search negative missing value");
}

// Tests 6-8: Traversals
void TestTraversals()
{
    BinarySearchTree<int> tree;
    FillTree(tree);

    int expectedInOrder[] = {20, 30, 40, 50, 60, 70, 80};
    int expectedPreOrder[] = {50, 30, 20, 40, 70, 60, 80};
    int expectedPostOrder[] = {20, 40, 30, 60, 80, 70, 50};

    ResetTraversal();
    tree.InOrder(CollectValue);

    Check(CheckTraversal(expectedInOrder, 7), "InOrder traversal");

    ResetTraversal();
    tree.PreOrder(CollectValue);

    Check(CheckTraversal(expectedPreOrder, 7), "PreOrder traversal");

    ResetTraversal();
    tree.PostOrder(CollectValue);

    Check(CheckTraversal(expectedPostOrder, 7), "PostOrder traversal");
}

// Test 9: BST validation
void TestIsValid()
{
    BinarySearchTree<int> tree;
    FillTree(tree);

    Check(tree.IsValid(), "BST representation invariant");

    tree.Insert(10);
    tree.Insert(90);

    Check(tree.IsValid(), "BST valid after additional insertions");
}

// Test 10: Copy constructor
void TestCopyConstructor()
{
    BinarySearchTree<int> original;
    FillTree(original);

    BinarySearchTree<int> copied(original);

    Check(copied.Search(50) && copied.Search(20) &&
          copied.Search(80), "Copy constructor preserves values");

    original.Insert(100);

    Check(!copied.Search(100), "Copy constructor performs deep copy");

    copied.Insert(5);

    Check(!original.Search(5), "Copied tree is independent");
}

// Test 11: Assignment operator
void TestAssignment()
{
    BinarySearchTree<int> original;
    FillTree(original);

    BinarySearchTree<int> assigned;
    assigned.Insert(999);

    assigned = original;

    Check(assigned.Search(50) && assigned.Search(30) &&
          assigned.Search(80), "Assignment copies values");

    Check(!assigned.Search(999), "Assignment replaces old contents");

    original.Insert(100);
    Check(!assigned.Search(100),"Assignment performs deep copy");
}

// Test 12: Self-assignment
void TestSelfAssignment()
{
    BinarySearchTree<int> tree;
    FillTree(tree);
    tree = tree;

    Check(tree.Search(50) && tree.Search(20) &&
          tree.Search(80), "Self-assignment preserves values");

    Check(tree.IsValid(), "Tree remains valid after self-assignment");
}

// Tests 13-14: Delete and reuse
void TestDeleteTree()
{
    BinarySearchTree<int> tree;
    FillTree(tree);

    tree.DeleteTree();

    Check(!tree.Search(50) && !tree.Search(20) &&
          !tree.Search(80), "DeleteTree removes all nodes");

    Check(tree.IsValid(), "Tree valid after deletion");
    Check(tree.Insert(100), "Insert after DeleteTree");
    Check(tree.Search(100), "Reused tree stores new value");
}

// Test 15: Empty tree operations
void TestEmptyTree()
{
    BinarySearchTree<int> tree;
    Check(!tree.Search(10), "Search empty tree");
    ResetTraversal();
    tree.InOrder(CollectValue);
    Check(traversalCount == 0, "Traverse empty tree");
    tree.DeleteTree();
    Check(tree.IsValid(), "Delete empty tree safely");
}

// Test 16: Copy empty tree
void TestEmptyCopy()
{
    BinarySearchTree<int> empty;
    BinarySearchTree<int> copied(empty);

    Check(copied.IsValid() && !copied.Search(10), "Copy empty tree");
    Check(copied.Insert(10) && copied.Search(10), "Copied empty tree remains usable");
}

// Test 17: Assign empty tree
void TestEmptyAssignment()
{
    BinarySearchTree<int> empty;
    BinarySearchTree<int> destination;
    FillTree(destination);
    destination = empty;

    Check(!destination.Search(50) && destination.IsValid(), "Assign empty tree");

    Check(destination.Insert(25), "Assigned empty tree remains usable");
}

// Test 18: Chronological insertion
void TestOrderedInsertion()
{
    BinarySearchTree<int> tree;
    bool inserted = true;

    for (int i = 1; i <= 50; i++)
    {
        if (!tree.Insert(i))
        {
            inserted = false;
        }
    }

    Check(inserted, "Insert 50 ascending values");

    Check(tree.IsValid(), "Ordered insertion maintains BST invariant");

    Check(tree.Search(1) && tree.Search(25) &&
          tree.Search(50), "Search ordered tree");

    ResetTraversal();
    tree.InOrder(CollectValue);

    bool ascending = traversalCount == 50;
    for (int i = 0; i < traversalCount; i++)
    {
        if (traversal[i] != i + 1)
        {
            ascending = false;
        }
    }
    Check(ascending, "Ordered tree traverses in ascending order");
}

// Test 19: Function pointer callback
void TestFunctionPointer()
{
    BinarySearchTree<int> tree;
    FillTree(tree);
    ResetTraversal();
    tree.InOrder(CollectValue);

    Check(traversalCount == 7, "Function pointer visits every node");
}

int main()
{
    cout << "====================================" << endl;
    cout << "           BST UNIT TESTS           " << endl;
    cout << "====================================" << endl;

    TestConstructor();
    TestInsert();
    TestDuplicate();
    TestSearch();
    TestTraversals();
    TestIsValid();
    TestCopyConstructor();
    TestAssignment();
    TestSelfAssignment();
    TestDeleteTree();
    TestEmptyTree();
    TestEmptyCopy();
    TestEmptyAssignment();
    TestOrderedInsertion();
    TestFunctionPointer();

    cout << endl << "====================================" << endl;
    cout << "              SUMMARY               " << endl;
    cout << "====================================" << endl;

    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "Total:  " << passed + failed << endl;

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
