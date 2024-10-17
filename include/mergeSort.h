#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include "arraylist.h"
using namespace std;
class mergeSort
{
private:
    /* data */
    arraylist<int> merge(arraylist<int> array1, arraylist<int> array2);
    arraylist<int> breakUp(arraylist<int> array, int low, int high);
public:
    mergeSort(/* args */);
    ~mergeSort();
    
    arraylist<int> sortArray(arraylist<int> array);
};

#endif MERGESORT_HPP