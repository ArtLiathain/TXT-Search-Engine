#include <vector>
#include <iostream>

#include "../include/mergeSort.h"

mergeSort::mergeSort()
{
}

mergeSort::~mergeSort()
{
}

// Entrypoint function
arraylist<pair<string, float>> mergeSort::sortArray(arraylist<pair<string, float>> array)
{
    if (array.length == 0) {
        return arraylist<pair<string, float>>();
    }
    return breakUp(array, 0, array.length - 1);
}

arraylist<pair<string, float>> mergeSort::breakUp(arraylist<pair<string, float>> array, int low, int high)
{

    // if high <= low a single value has been picked to be sorted and used as base for merge sort
    if (high <= low)
    {
        // Create and return a single element array at low index
        arraylist<pair<string, float>> lowValueArr = arraylist<pair<string, float>>(1);
        lowValueArr.insert(array.get(low));
        return lowValueArr;
    }
    // Get mid mpoint
    int mid = (high + low) / 2;
    // recursive call with breakUp to get to single values to then merge up to the full array
    return merge(breakUp(array, low, mid), breakUp(array, mid + 1, high));
}

arraylist<pair<string, float>> mergeSort::merge(arraylist<pair<string, float>> array1, arraylist<pair<string, float>> array2)
{

    int pointer1 = 0;
    int pointer2 = 0;
    int arr1Size = array1.length;
    int arr2Size = array2.length;

    //Allocate new array with the exact capacity needed
    arraylist<pair<string, float>> newArr = arraylist<pair<string, float>>(arr1Size + arr2Size);
    // Loop over until one pointer has has reached their capacity
    while (pointer1 < arr1Size && pointer2 < arr2Size)
    {
        // insert the largest value first and increment that sides pointer
        if (array1.get(pointer1).second > array2.get(pointer2).second)
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
    // Append the rest of the values to the end of the combined array getting using all values
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
