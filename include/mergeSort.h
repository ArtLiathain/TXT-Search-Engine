#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include "arraylist.h"
using namespace std;
class mergeSort
{

public:
    mergeSort();
    ~mergeSort();

    arraylist<pair<string, float>> sortArray(arraylist<pair<string, float>> array);

private:

    arraylist<pair<string, float>> merge(arraylist<pair<string, float>>  array1, arraylist<pair<string, float>>  array2);
    arraylist<pair<string, float>>  breakUp(arraylist<pair<string, float>> array, int low, int high);
};

#endif MERGESORT_HPP