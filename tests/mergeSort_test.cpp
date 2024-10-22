#include <gtest/gtest.h>
#include "../include/arraylist.h"
#include "../include/mergeSort.h"

using namespace std;

// Test sorting an already sorted array
TEST(mergeSort_test, reverseSorted)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(5);
    array.insert(pair{"book1", 1});
    array.insert(pair{"book2", 2});
    array.insert(pair{"book3", 3});
    array.insert(pair{"book4", 4});
    array.insert(pair{"book5", 5});

    arraylist<pair<string, float>> sortedArray = merge.sortArray(array);

    for (int i = 1; i < sortedArray.length; i++)
    {
        ASSERT_TRUE(sortedArray.get(i - 1).second >= sortedArray.get(i).second);
    }
}

// Test sorting an empty array
TEST(mergeSort_test, emptyArray)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(1);

    arraylist<pair<string, float>> sortedArray = merge.sortArray(array);

    ASSERT_EQ(sortedArray.length, 0);
}

// Test sorting a single element array
TEST(mergeSort_test, singleElement)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(1);
    array.insert(pair{"book1", 1});

    arraylist<pair<string, float>> sortedArray = merge.sortArray(array);

    ASSERT_EQ(sortedArray.length, 1);
    ASSERT_EQ(sortedArray.get(0).second, 1);
}

// Test sorting an array where all elements have the same value
TEST(mergeSort_test, sameValues)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(5);
    array.insert(pair{"book1", 2});
    array.insert(pair{"book2", 2});
    array.insert(pair{"book3", 2});
    array.insert(pair{"book4", 2});
    array.insert(pair{"book5", 2});

    arraylist<pair<string, float>> sortedArray = merge.sortArray(array);

    for (int i = 1; i < sortedArray.length; i++)
    {
        ASSERT_TRUE(sortedArray.get(i - 1).second == sortedArray.get(i).second);
    }
}

// Test sorting a reverse-sorted array
TEST(mergeSort_test, alreadySorted)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(5);
    array.insert(pair{"book5", 5});
    array.insert(pair{"book4", 4});
    array.insert(pair{"book3", 3});
    array.insert(pair{"book2", 2});
    array.insert(pair{"book1", 1});

    arraylist<pair<string, float>> sortedArray = merge.sortArray(array);

    for (int i = 1; i < sortedArray.length; i++)
    {
        ASSERT_TRUE(sortedArray.get(i - 1).second >= sortedArray.get(i).second);
    }
}

// Test sorting a large array
TEST(mergeSort_test, largeArray)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(1000);
    for (int i = 0; i < 1000; i++)
    {
        array.insert(pair{"book" + to_string(i), rand() % 1000});
    }

    arraylist<pair<string, float>> sortedArray = merge.sortArray(array);

    for (int i = 1; i < sortedArray.length; i++)
    {
        ASSERT_TRUE(sortedArray.get(i - 1).second >= sortedArray.get(i).second);
    }
}