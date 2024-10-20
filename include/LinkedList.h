#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList
{
private:
    

    int length;

public:
struct Node
    {
        T data;
        Node *next;
    };
    Node *head;
    LinkedList();
    ~LinkedList();
    
    void add(const T &value, int index = 0);
    T pop(int index);
    T get(int index) const;
    int size() const;
};

// Constructor
template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    length = 0;
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Add a node at the specified index
template <typename T>
void LinkedList<T>::add(const T &value, int index)
{
    if (index < 0 || index > length)
    {
        throw std::out_of_range("Index out of bounds");
    }

    Node *newNode = new Node();
    newNode->data = value;

    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node *current = head;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    length++;
}

// Remove and return the node at the specified index
template <typename T>
T LinkedList<T>::pop(int index)
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of bounds");
    }

    Node *toDelete;
    T returnValue;

    if (index == 0)
    {
        toDelete = head;
        returnValue = head->data;
        head = head->next;
    }
    else
    {
        Node *current = head;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        toDelete = current->next;
        returnValue = toDelete->data;
        current->next = toDelete->next;
    }

    delete toDelete;
    length--;
    return returnValue;
}

// Get the value of the node at the specified index
template <typename T>
T LinkedList<T>::get(int index) const
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of bounds");
    }

    Node *current = head;
    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return current->data;
}



// Return the size of the list
template <typename T>
int LinkedList<T>::size() const
{
    return length;
}

#endif
