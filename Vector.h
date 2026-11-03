#ifndef VECTOR_H
#define VECTOR_H

/**
 * @author  Marcus
 * @version 3.0
 * @date 3/11/2026
 */

#include <stdexcept>

/**
 * @brief A dynamic array template that stores elements of type T
 *
 * The Vector class provides CRUD functions for a dynamic array
 * It manages its own dynamically allocated memory and automatically increases its capacity when the Vector becomes full
 *
 * @tparam T The type of elements stored in the Vector
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Default constructor
     *
     * Creates an empty Vector with a default capacity
     */
    Vector();

    /**
     * @brief Parameterised constructor
     *
     * Creates an empty Vector with a specified initial capacity
     *
     * @param n The initial capacity of the Vector
     */
    Vector(int n);

    /**
     * @brief Destructor
     *
     * Releases the dynamically allocated memory occupied by the Vector
     */
    ~Vector();

    // Deep copying methods
    /**
     * @brief Copy constructor
     *
     * Creates a deep copy of another Vector
     *
     * @param other The Vector to be copied
     */
    Vector(const Vector<T>& other);

    /**
     * @brief Assignment operator
     *
     * Copies the contents of another Vector into this Vector
     * Deep copying is performed so both Vectors have separate dynamically allocated arrays
     *
     * @param other The Vector to be copied
     * @return A reference to this Vector
     */
    Vector<T>& operator=(const Vector<T>& other);

    // ========================================
    //              CRUD Functions
    // ========================================

    // Create
    /**
     * @brief A function to insert an element into the Vector
     *
     * The element is inserted at the specified position
     * Existing elements from that position onwards are shifted to the right by one position
     *
     * If the Vector is full, its capacity is increased before the element is inserted
     *
     * @param pos The position where the element will be inserted
     * @param data The data to be inserted
     * @return true if the element was successfully inserted, false if the position is invalid
     */
    bool Insert(int pos, const T& data);

    // Delete
    /**
     * @brief A function to remove an element from the Vector
     *
     * The element at the specified position is removed
     * Existing elements from that position onwards are shifted to the left by one position
     *
     * @param pos The position of the element to be remoeved
     * @return true if the element was successfully removed, false if the position is invalid
     */
    bool Remove(int pos);

    // Read
    /**
     * @brief A function to provide read-only access to an element
     *
     * Returns the element at the specified position without allowing modifications to the element
     *
     * @param pos The position of the element to access
     * @return A constant reference to the element at the specified position
     * @throws std::out_of_range If the position is outside the range of stored elements
     */
    const T& operator[](int pos) const;

    // Update
    /**
     * @brief A function to provide update access to an element
     *
     * Returns the element at the specified position by reference, allowing modifications to the element
     *
     * @param pos The position of the element to access
     * @return A reference to the element at the specified position
     * @throws std::out_of_range If the position is outside the range of stored elements
     */
    T& operator[](const int& pos);


    /**
     * @brief Returns the number of elements currently stored
     *
     * @return The current number of elements in the Vector
     */
    int Size() const;

    /**
     * @brief Performs a linear search to filter if any records are duplicated
     *
     * @param item Passes each new record by reference for comparison
     * @return True if item matches past records, false if does not exist
     */
    bool Exists(const T& item) const;

private:

    /**
     * @brief The total number of elements that can be stored currently
     */
    int m_capacity;

    /**
     * @brief The current number of elements that are stored
     */
    int m_size;

    /**
     * @brief Pointer to the dynamically allocated array of elements
     */
    T * m_vector;

    /**
     * @brief Function to increatse the capacity of the Vector
     *
     * Creates a new dynamic array with a larger capacity
     * Existing elements are copied into the new array and deletes the old array, releasing the memory stored
     */
    void Resize();

    /**
     * @brief Creates a deep copy of another Vector's array
     *
     * Allocates a new array and copies the stored elements.
     *
     * @param other The Vector to copy
     * @return Pointer to the newly allocated array
     */
    T* CopyArray(const Vector<T>& other) const;

};  // End of interface/declaration of the template class

// Default constructor
template <class T>
Vector<T>::Vector()
{
    m_vector = new T[100];
    m_size = 0;
    if (m_vector != nullptr)
    {
        m_capacity = 100;
    }
    else
    {
        m_capacity = 0;
    }
}

// Parameterised constructor
template <class T>
Vector<T>::Vector(int n)
{
    if (n < 0)
    {
        throw std::invalid_argument("Vector size cannot be less than 0");
    }

    m_size = n;
    if (n == 0)
    {
        m_capacity = 2;
    }
    else
    {
        m_capacity = n * 2;
    }
    m_vector = new T[m_capacity]{};
}

// Destructor
template <class T>
Vector<T>::~Vector()
{
    delete[] m_vector;
}

// Copy Constructor
template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_vector = CopyArray(other);
    m_capacity = other.m_capacity;
    m_size = other.m_size;
}

// Assignment operator
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        Vector<T> temp(other);

        T* oldVector = m_vector;
        int oldCapacity = m_capacity;
        int oldSize = m_size;

        m_vector = temp.m_vector;
        m_capacity = temp.m_capacity;
        m_size = temp.m_size;

        temp.m_vector = oldVector;
        temp.m_capacity = oldCapacity;
        temp.m_size = oldSize;
    }
    return *this;
}

// Create
template <class T>
bool Vector<T>::Insert(int pos, const T & data)
{
    // If pos is out of bounds
    if (pos < 0 || pos > m_size)
    {
        return false;
    }

    // If Vector is full, resize
    if (m_size == m_capacity)
    {
        Resize();
    }

    // Check if vector is full
    if (m_size < m_capacity)
    {
        // If position is not the end
        if (pos != m_size)
        {
            // move elements to the right
            for (int i = m_size; i > pos; i--)
            {
                m_vector[i] = m_vector[i-1];
            }
            m_vector[pos] = data;
        }
        else
        {
            // Append instead
            m_vector[pos] = data;
        }
        m_size++;
        return true;
    }
    return false;
}

// Delete
template <class T>
bool Vector<T>::Remove(int pos)
{
    // Check if pos is out of bounds
    if (pos < 0 || pos >= m_size)
    {
        return false;
    }
    // Shift the elements to the left
    for (int i = pos; i < m_size - 1; i++)
    {
        m_vector[i] = m_vector[i + 1];
    }
    m_size--;

    return true;
}


// Read
template <class T>
const T& Vector<T>::operator[](int pos) const
{
    // If out of bounds, throw exception
    if (pos < 0 || pos >= m_size)
    {
        throw std::out_of_range("Vector position out of bounds");
    }
    return m_vector[pos];
}

// Update
template <class T>
T& Vector<T>::operator[](const int& pos)
{
    // If out of bounds, throw exception
    if (pos < 0 || pos >= m_size)
    {
        throw std::out_of_range("Vector position out of bounds");
    }
    return m_vector[pos];
}

// Return number of elements currently stored
template <class T>
int Vector<T>::Size() const
{
    return m_size;
}

// Exists
template <class T>
bool Vector<T>::Exists(const T& item) const
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_vector[i] == item)
        {
            return true;
        }
    }
    return false;
}

// Resize
template <class T>
void Vector<T>::Resize()
{
    int newCapacity;
    if (m_capacity == 0)
    {
        newCapacity = 2;
    }
    else
    {
        newCapacity = m_capacity * 2;
    }

    T* newVector = new T[newCapacity];

    try
    {
        for (int i = 0; i < m_size; i++)
        {
            newVector[i] = m_vector[i];
        }
    }
    catch(...)
    {
        delete[] newVector;
        throw;
    }

    delete[] m_vector;
    m_vector = newVector;;;
    m_capacity = newCapacity;
}

template <class T>
T* Vector<T>::CopyArray(const Vector<T>& other) const
{
    T* newVector = new T[other.m_capacity];

    try
    {
        for (int i = 0; i < other.m_size; i++)
        {
            newVector[i] = other.m_vector[i];
        }
    }
    catch (...)
    {
        delete[] newVector;
        throw;
    }
    return newVector;
}

#endif
