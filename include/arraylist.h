#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <iostream>

template <typename T>
class arraylist
{
private:
    T *array;

public:
    arraylist(int _capacity);
    arraylist();
    arraylist(const arraylist<T>& other);
    arraylist& operator=(const arraylist<T>& other);
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


template <typename T>
arraylist<T>::arraylist(const arraylist<T>& other)
{
    capacity = other.capacity;
    length = other.length;
    array = new T[capacity];
    for (int i = 0; i < length; ++i)
    {
        array[i] = other.array[i];
    }
}

template <typename T>
arraylist<T>& arraylist<T>::operator=(const arraylist<T>& other)
{
    if (this == &other) 
        return *this;


    delete[] array;


    capacity = other.capacity;
    length = other.length;
    array = new T[capacity];
    for (int i = 0; i < length; ++i)
    {
        array[i] = other.array[i];
    }

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
    if(index >= capacity || index >= length){
        throw std::out_of_range("Index out of bounds");
    }
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
}

template <typename T>
void arraylist<T>::insert(T value)
{
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
}

template <typename T>
void arraylist<T>::remove(int index)
{
    if (length == 0 && index -1 > length)
    {
        throw std::out_of_range("Index out of bounds");
    }
    for (int i = index + 1; i < length; i++)
    {
        array[i - 1] = array[i];
    }
    length--;
}

template <typename T>
T arraylist<T>::get(int index)
{
    if (index >= 0 && index < length)
    {
        return array[index];
    }
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
arraylist<T>::~arraylist()
{
    delete[] array;
}

#endif