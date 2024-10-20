#include <gtest/gtest.h>
#include "../include/serialiseArraylist.h"

TEST(serialiseArraylist_test, full_test)
{
    arraylist<pair<string, float>> originalArray = arraylist<pair<string, float>>(15);

    originalArray.insert(pair("apple", 1.2f));
    originalArray.insert(pair("banana", 0.8f));
    originalArray.insert(pair("orange", 1.5f));

    serialiseArraylist serialiser = serialiseArraylist();
    string serializedData = serialiser.serialiseArraylistIntoString(originalArray);

    arraylist<pair<string, float>> deserializedArray = serialiser.deserialiseintoArraylist(serializedData);

    for (size_t i = 0; i < originalArray.length; ++i)
    {
        ASSERT_EQ(originalArray.get(i), deserializedArray.get(i));
    }
}