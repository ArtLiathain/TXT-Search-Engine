#include <gtest/gtest.h>
#include "../include/arraylist.h"
#include "../include/mergeSort.h"

using namespace std;

TEST(mergeSort_test, initialise)
{
    mergeSort merge = mergeSort();

    arraylist<pair<string, float>> array = arraylist<pair<string, float>>(10);
    array.insert(pair{"book1", 1});
    array.insert(pair{"book4", 4});
    array.insert(pair{"book10", 10});
    array.insert(pair{"book6", 6});
    array.insert(pair{"book2", 2});
    array.insert(pair{"book8", 6});
    array.insert(pair{"book5", 5});
    array.insert(pair{"book3", 3});
    array.insert(pair{"book3", 3});
    array.insert(pair{"book7", 6});
    array.insert(pair{"book9", 9});

    arraylist<pair<string, float>> newArray = merge.sortArray(array);

    for (int i = 1; i < newArray.length; i++)
    {
        ASSERT_TRUE(newArray.get(i - 1).second >= newArray.get(i).second);
    }
}