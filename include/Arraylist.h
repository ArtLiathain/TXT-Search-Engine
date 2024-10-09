#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <iostream>

template <typename T>
class Arraylist
{
private:
    T *array;

public:
    Arraylist(int _capacity);
    ~Arraylist();
    int capacity;
    int length;
    void insert(T value);
    void insert(T value, int index);
    void remove(int index);
    T get(int index);
};

template <typename T>
Arraylist<T>::Arraylist(int _capacity)
{
    array = new T[_capacity];
    length = 0;
    capacity = _capacity;
}

template <typename T>
void Arraylist<T>::insert(T value, int index)
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
void Arraylist<T>::insert(T value)
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
void Arraylist<T>::remove(int index)
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
T Arraylist<T>::get(int index)
{
    if (index >= 0 && index < length)
    {
        return array[index];
    }
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
Arraylist<T>::~Arraylist()
{
    delete[] array;
}

#endif