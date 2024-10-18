#include <vector>
#include <iostream>

#include "../include/mergeSort.h"

mergeSort::mergeSort()
{
}

mergeSort::~mergeSort()
{
}

arraylist<pair<string, float>> mergeSort::sortArray(arraylist<pair<string, float>> array)
{
    return breakUp(array, 0, array.length - 1);
}

arraylist<pair<string, float>> mergeSort::breakUp(arraylist<pair<string, float>> array, int low, int high)
{

    if (high <= low)
    {

        arraylist<pair<string, float>> lowValueArr = arraylist<pair<string, float>>(1);
        lowValueArr.insert(array.get(low));
        return lowValueArr;
    }
    int mid = (high + low) / 2;
    return merge(breakUp(array, low, mid), breakUp(array, mid + 1, high));
}

arraylist<pair<string, float>> mergeSort::merge(arraylist<pair<string, float>> array1, arraylist<pair<string, float>> array2)
{

    int pointer1 = 0;
    int pointer2 = 0;
    int arr1Size = array1.length;
    int arr2Size = array2.length;

    arraylist<pair<string, float>> newArr = arraylist<pair<string, float>>(arr1Size + arr2Size);
    while (pointer1 < arr1Size && pointer2 < arr2Size)
    {

        if (array1.get(pointer1).second < array2.get(pointer2).second)
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
    for (int i = 0; i < newArr.length; i++)
    {
        cout << newArr.get(i).second << " ";
    }
    cout << endl;
    return newArr;
}
