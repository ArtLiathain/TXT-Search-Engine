#include <vector>
#include <iostream>

#include "../include/mergeSort.h"


mergeSort::mergeSort(/* args */)
{
}

mergeSort::~mergeSort()
{
}

arraylist<int> mergeSort::sortArray(arraylist<int> array)
{
    return breakUp(array, 0, array.length - 1);
}

arraylist<int> mergeSort::breakUp(arraylist<int> array, int low, int high)
{
    if (high <= low)
    {
        return arraylist<int>{array.get(low)};
    }
    int mid = (high + low) / 2;
    return merge(breakUp(array, low, mid), breakUp(array, mid + 1, high));
}

arraylist<int> mergeSort::merge(arraylist<int> array1, arraylist<int> array2)
{
    int pointer1 = 0;
    int pointer2 = 0;
    int arr1Size = array1.length;
    int arr2Size = array2.length;
    arraylist<int> newArr = arraylist<int>(10);
    while (pointer1 < arr1Size && pointer2 < arr2Size)
    {
        if (array1.get(pointer1) < array2.get(pointer2))
        {
            newArr.insert(array1.get(pointer1));
            pointer1++;
        }
        else
        {
            newArr.insert(array2.get(pointer2));
            pointer2++;
        }
    }
    while (pointer1 < arr1Size)
    {
        newArr.insert(array1.get(pointer1));
        pointer1++;
    }
    while (pointer2 < arr2Size)
    {
        newArr.insert(array2.get(pointer2));
        pointer2++;
    }
    return newArr;
}

