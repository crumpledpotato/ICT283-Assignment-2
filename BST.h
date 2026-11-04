#ifndef BST_H
#define BST_H

/**
 * @author  Marcus
 * @version 2.0
 * @date 29/10/2026
 *
 * @file Bst.h
 * @brief Defines a templated Binary Search Tree.
 *
 * This file contains the Bst class, which stores elements of type T in a Binary Search Tree.
 * The tree supports insertion, searching, copying, deletion, validation and tree traversal.
 */

#include <iostream>

/**
 * @brief Stores an individual node in the Binary Search Tree.
 *
 * @tparam T Data type stored in the node.
 */
template <class T>
struct nodeType
{
    T info;
    nodeType<T>* lLink;
    nodeType<T>* rLink;

    /**
     * @brief Constructs a node.
     * @param value Value to store in the node.
     */
    nodeType(const T& value)
    {
        info = value;
        lLink = nullptr;
        rLink = nullptr;
    }
};

/**
 * @class BinarySearchTree
 * @brief A templated Binary Search Tree.
 *
 * The Binary Search Tree stores values according to the following representation invariant : <br>
 * All values in the left subtree are smaller than the current node. <br>
 * All values in the right subtree are greater than the current node. <br>
 * Duplicate values are not permitted.<br>
 *
 * @tparam T The data type stored in the tree.
 * The type must support the less-than operator (<), copy constructor and assignment operator. <br>
 */
template <class T>
class BinarySearchTree
{
public:

    /**
     * @brief Function pointer type for traversal callbacks.
     *
     * @param T& Reference to the value stored in the current node.
     */
    typedef void (*f1Typ)(T&);

    /**
     * @brief Default constructor.
     *
     * Creates an empty Binary Search Tree.
     */
    BinarySearchTree();

    /**
     * @brief Destructor.
     *
     * Releases all dynamically allocated nodes in the tree.
     */
    ~BinarySearchTree();

    /**
     * @brief Copy constructor.
     *
     * Creates a deep copy of another Binary Search Tree.
     *
     * @param other The existing tree to copy.
     */
    BinarySearchTree(const BinarySearchTree& other);

    /**
     * @brief Assignment operator.
     *
     * Replaces the current tree with a deep copy of another tree.
     *
     * @param other The tree to assign from.
     * @return Reference to the current tree.
     */
    BinarySearchTree& operator=(const BinarySearchTree& other);

    // ======= Basic Functions ======

    /**
     * @brief Inserts a value into the tree.
     *
     * Recursively finds the correct position for the new value. <br>
     * Duplicate values are rejected.
     *
     * @param value The value to insert.
     * @return true if insertion succeeds, false if the value already exists.
     */
    bool Insert(const T& value);

    /**
     * @brief Searches for a value in the tree.
     *
     * @param value The value to search for.
     * @return true if the value is found, otherwise false.
     */
    bool Search(const T& value) const;

    /**
     * @brief Deletes all nodes in the tree.
     *
     * After deletion, the tree becomes empty.
     */
    void DeleteTree();

    /**
     * @brief Checks the Binary Search Tree representation invariant.
     *
     * Verifies that every node follows the Binary Search Tree ordering rules and that duplicate values do not exist.
     *
     * @return true if the tree is valid, otherwise false.
     */
    bool IsValid() const;

    /**
     * @brief Returns the number of nodes in the BST.
     *
     * @return Total number of nodes.
     */
    int Size() const;

    // ====== Traversals ======

    /**
     * @brief Performs an in-order traversal using a callback function.
     * @param f1 Function to execute for each stored value.
     */
    void InOrder(f1Typ f1) const;

    /**
     * @brief Performs a pre-order traversal using a callback function.
     * @param f1 Function to execute for each stored value.
     */
    void PreOrder(f1Typ f1) const;

    /**
     * @brief Performs a post-order traversal using a callback function.
     * @param f1 Function to execute for each stored value.
     */
    void PostOrder(f1Typ f1) const;

private:

    /**
     * @brief Pointer to the root node of the Binary Search Tree.
     *
     * If root is nullptr, the tree is empty.
     */
    nodeType<T>* root;

    // ====== Recursive helpers ======

    /**
     * @brief Recursive insertion helper.
     *
     * Finds the correct position and inserts a new node.
     *
     * @param node Reference to the current node pointer.
     * @param value Value to insert.
     * @return true if inserted, otherwise false.
     */
    bool Insert(nodeType<T>*& node, const T& value);

    /**
     * @brief Recursive search helper.
     *
     * @param node Pointer to the current node.
     * @param value Value to search for.
     * @return true if found, otherwise false.
     */
    bool Search(nodeType<T>* node, const T& value) const;

    /**
     * @brief Recursive tree deletion helper.
     *
     * Deletes the current node and all its children.
     *
     * @param node Pointer to the current node.
     */
    void DeleteTree(nodeType<T>* node);

    /**
     * @brief Creates a deep copy of a subtree.
     *
     * @param node Pointer to the subtree being copied.
     * @return Pointer to the root of the newly copied subtree.
     */
    nodeType<T>* CopyTree(const nodeType<T>* node);

    /**
     * @brief Recursive representation invariant checker.
     *
     * Checks whether each node satisfies the lower and upper value boundaries of the Binary Search Tree.
     *
     * @param node Pointer to the current node.
     * @param lower Lower boundary allowed for the current node.
     * @param upper Upper boundary allowed for the current node.
     * @return true if the subtree is valid, otherwise false.
     */
    bool IsValid(const nodeType<T>* node, const T* lower, const T* upper) const;

    /**
     * @brief Recursively counts the nodes in a subtree.
     *
     * @param node Root of the subtree.
     * @return Number of nodes in the subtree.
     */
    int CountNodes(const nodeType<T>* node) const;

    // ====== Traversals ======

    /**
     * @brief Recursive in-order traversal helper.
     *
     * @param f1 Function to execute for each stored value.
     * @param node Pointer to the current node.
     */
    void InOrder(f1Typ f1, nodeType<T>* node) const;

    /**
     * @brief Recursive pre-order traversal helper.
     *
     * @param f1 Function to execute for each stored value.
     * @param node Pointer to the current node.
     */
    void PreOrder(f1Typ f1, nodeType<T>* node) const;

    /**
     * @brief Recursive post-order traversal helper.
     *
     * @param f1 Function to execute for each stored value.
     * @param node Pointer to the current node.
     */
    void PostOrder(f1Typ f1, nodeType<T>* node) const;
};

// Constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}

// Destructor
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    DeleteTree();
}

// Copy constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other)
{
    root = CopyTree(other.root);
}

// Assignment operator
template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other)
{
    if (this != &other)
    {
        BinarySearchTree<T> temp(other);
        nodeType<T>* tempRoot = root;
        root = temp.root;
        temp.root = tempRoot;
    }
    return *this;
}

// ====== Create/Insert =======
template <class T>
bool BinarySearchTree<T>::Insert(const T& value)
{
    return Insert(root, value);
}

template <class T>
bool BinarySearchTree<T>::Insert(nodeType<T>*& node, const T& value)
{
    if (node == nullptr)
    {
        node = new nodeType<T>(value);
        return true;
    }

    if (value < node->info)
    {
        return Insert(node->lLink, value);
    }
    else if (node->info < value)
    {
        return Insert(node->rLink, value);
    }

    // Duplicates are not inserted
    return false;
}

// ====== Read ======
template <class T>
bool BinarySearchTree<T>::Search(const T& value) const
{
    return Search(root, value);
}

template <class T>
bool BinarySearchTree<T>::Search(nodeType<T>* node, const T& value) const
{
   if (node == nullptr)
   {
       return false;
   }
   // If value matches data
   if (!(value < node->info) && !(node->info < value))
   {
       return true;
   }

   if (value < node->info)
   {
       return Search(node->lLink, value);
   }

   return Search(node->rLink, value);
}

// ====== Delete =======
template <class T>
void BinarySearchTree<T>::DeleteTree()
{
    DeleteTree(root);
    root = nullptr;
}

template <class T>
void BinarySearchTree<T>::DeleteTree(nodeType<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    DeleteTree(node->lLink);
    DeleteTree(node->rLink);
    delete node;
}

template <class T>
nodeType<T>* BinarySearchTree<T>::CopyTree(const nodeType<T>* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    nodeType<T>* newNode = new nodeType<T>(node->info);

    try
    {
        newNode->lLink = CopyTree(node->lLink);
        newNode->rLink = CopyTree(node->rLink);
    }
    catch(...)
    {
        DeleteTree(newNode);
        throw;
    }
    return newNode;
}

// Check Representation Invariant
template <class T>
bool BinarySearchTree<T>::IsValid() const
{
    return IsValid(root, nullptr, nullptr);
}

template <class T>
bool BinarySearchTree<T>::IsValid(const nodeType<T>* node, const T* lower, const T* upper) const
{
    if (node == nullptr)
    {
        return true;
    }

    if (lower != nullptr && !(*lower < node->info))
    {
        return false;
    }
    if (upper != nullptr && !(node->info < *upper))
    {
        return false;
    }

    return IsValid(node->lLink, lower, &node->info) &&
           IsValid(node->rLink, &node->info, upper);
}

// ====== Check size of BST ======
template <class T>
int BinarySearchTree<T>::Size() const
{
    return CountNodes(root);
}

template <class T>
int BinarySearchTree<T>::CountNodes(const nodeType<T>* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + CountNodes(node->lLink) + CountNodes(node->rLink);
}

// ====== In Order Traversals ======
template <class T>
void BinarySearchTree<T>::InOrder(f1Typ f1) const
{
    InOrder(f1, root);
}

template <class T>
void BinarySearchTree<T>::InOrder(f1Typ f1, nodeType<T>* node) const
{
    if (node == nullptr)
    {
        return;
    }

    InOrder(f1, node->lLink);
    f1(node->info);
    InOrder(f1, node->rLink);
}

// ====== PreOrder Traversals ======
template <class T>
void BinarySearchTree<T>::PreOrder(f1Typ f1) const
{
    PreOrder(f1, root);
}

template <class T>
void BinarySearchTree<T>::PreOrder(f1Typ f1, nodeType<T>* node) const
{
    if (node == nullptr)
    {
        return;
    }

    f1(node->info);
    PreOrder(f1, node->lLink);
    PreOrder(f1, node->rLink);
}

// ====== PostOrder Traversals ======
template <class T>
void BinarySearchTree<T>::PostOrder(f1Typ f1) const
{
    PostOrder(f1, root);
}

template <class T>
void BinarySearchTree<T>::PostOrder(f1Typ f1, nodeType<T>* node) const
{
    if (node == nullptr)
    {
        return;
    }

    PostOrder(f1, node->lLink);
    PostOrder(f1, node->rLink);
    f1(node->info);
}

#endif
