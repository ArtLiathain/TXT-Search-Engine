#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <iostream>

template <typename T>
class Arraylist
{
private:
    T *array;

public:
    Arraylist(int size);
    ~Arraylist();
    int length;
    int capacity;
    void add(T value, int index);
    void pop(int index);
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
void Arraylist<T>::add(T value, int index)
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

    for (int i = length; i > index; i--)
    {
        array[i] = array[i - 1];
    }
    array[index] = value;
    length++;
}

template <typename T>
void Arraylist<T>::pop(int index)
{
    if (length == 0)
    {
        return;
    }
    length--;
    array[length] = 0;
}

template <typename T>
T Arraylist<T>::get(int index)
{
    if (index >= 0 && index < capacity)
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