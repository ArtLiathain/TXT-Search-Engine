#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <iostream>
#include <mutex>

template <typename T>
class arraylist
{
private:
    T *array;
    std::mutex readMutex;
    std::mutex writeMutex;

public:
    arraylist(int _capacity);
    arraylist();
    arraylist(const arraylist<T> &other);
    arraylist &operator=(const arraylist<T> &other);
    ~arraylist();
    int capacity;
    int length;
    void insert(T value);
    void insert(T value, int index);
    void remove(int index);
    T get(int index);
};

template <typename T>
arraylist<T>::arraylist()
{
    capacity = 100;
    array = new T[capacity];
    length = 0;
}

// Copy constructor to allow you to instantiate a copy of an arraylist when creating a new one
template <typename T>
arraylist<T>::arraylist(const arraylist<T> &other)
{
    // Use values from the other arraylsit when creating
    capacity = other.capacity;
    length = other.length;
    array = new T[capacity];
    for (int i = 0; i < length; ++i)
    {
        array[i] = other.array[i];
    }
}

// Assignment operator to allow = to deep copy
template <typename T>
arraylist<T> &arraylist<T>::operator=(const arraylist<T> &other)
{
    // if it is copying to itself, don't
    if (this == &other)
        return *this;

    // free up the memory in this instance of the array
    delete[] array;

    // Copy values over from the array being copied
    capacity = other.capacity;
    length = other.length;
    // Allocate the right amount of memory for the array
    array = new T[capacity];
    // Populate values
    for (int i = 0; i < length; ++i)
    {
        array[i] = other.array[i];
    }
    // Return pointer to this array
    return *this;
}

template <typename T>
arraylist<T>::arraylist(int _capacity)
{
    array = new T[_capacity];
    length = 0;
    capacity = _capacity;
}

template <typename T>
void arraylist<T>::insert(T value, int index)
{
    if (index >= capacity || index >= length)
    {
        throw std::out_of_range("Index out of bounds");
    }
    readMutex.lock();
    writeMutex.lock();

    if (length >= capacity)
    {
        T *newArray = new T[capacity * 2];
        for (int i = 0; i < length; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        capacity *= 2;
        array = newArray;
    }

    for (int i = length; i > index; i--)
    {
        array[i] = array[i - 1];
    }
    length++;
    array[index] = value;
    writeMutex.unlock();
    readMutex.unlock();
}

template <typename T>
void arraylist<T>::insert(T value)
{

    readMutex.lock();
    writeMutex.lock();
    if (length >= capacity)
    {
        T *newArray = new T[capacity * 2];
        for (int i = 0; i < length; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        capacity *= 2;
        array = newArray;
    }
    array[length] = value;
    length++;
    writeMutex.unlock();
    readMutex.unlock();
}

template <typename T>
void arraylist<T>::remove(int index)
{
    if (length == 0 && index - 1 > length)
    {
        throw std::out_of_range("Index out of bounds");
    }

    readMutex.lock();
    writeMutex.lock();

    for (int i = index + 1; i < length; i++)
    {
        array[i - 1] = array[i];
    }

    length--;
    writeMutex.unlock();
    readMutex.unlock();
}

template <typename T>
T arraylist<T>::get(int index)
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of bounds");
    }
    readMutex.lock();
    readMutex.unlock();
    return array[index];
}

template <typename T>
arraylist<T>::~arraylist()
{
    delete[] array;
}

#endif