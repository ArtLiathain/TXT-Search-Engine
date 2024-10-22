#include <gtest/gtest.h>
#include "../include/hashmap.h"
using namespace std;

TEST(hashmap_test, initialise)
{
    stringhashmap<int> hashmap = stringhashmap<int>(2);
    ASSERT_EQ(hashmap.MAXN, 2);
}

TEST(hashmap_test, insert)
{
    stringhashmap<int> hashmap = stringhashmap<int>(2);
    hashmap.insert("Test1", 42);
    ASSERT_EQ(hashmap.getValue("Test1"), 42);
}

TEST(hashmap_test, insertIntoFullMap)
{
    stringhashmap<int> hashmap = stringhashmap<int>(1);
    hashmap.insert("Test1", 42);
    hashmap.insert("Test2", 52);
    hashmap.insert("Test3", 12);
    hashmap.insert("Test4", 72);
    ASSERT_EQ(hashmap.getValue("Test1"), 42);
    ASSERT_EQ(hashmap.getValue("Test2"), 52);
    ASSERT_EQ(hashmap.getValue("Test3"), 12);
    ASSERT_EQ(hashmap.getValue("Test4"), 72);
}

TEST(hashmap_test, keyNotPresent)
{
    stringhashmap<int> hashmap = stringhashmap<int>(2);
    ASSERT_THROW(hashmap.getValue("Test1"), std::out_of_range);
}

TEST(hashmap_test, keyNotPresentAndKeyExistsCalled)
{
    stringhashmap<int> hashmap = stringhashmap<int>(2);
    ASSERT_FALSE(hashmap.keyExists("Test1"));
}

TEST(hashmap_test, getAllKeys)
{
    stringhashmap<int> hashmap = stringhashmap<int>(1);
    hashmap.insert("Test1", 42);
    hashmap.insert("Test2", 52);
    hashmap.insert("Test3", 12);
    hashmap.insert("Test4", 72);
    ASSERT_EQ(hashmap.getAllKeys().length, 4);
}

TEST(hashmap_test, insertAndRemove)
{
    
    stringhashmap<int> hashmap = stringhashmap<int>(2);
    hashmap.insert("Test1", 42);
    ASSERT_EQ(hashmap.getValue("Test1"), 42);
    hashmap.remove("Test1");
    ASSERT_THROW(hashmap.getValue("Test1"), std::out_of_range);
}

TEST(hashmap_test, serialize)
{
    arraylist<pair<string, arraylist<pair<string, float>>>> keyFloatPairs = arraylist<pair<string, arraylist<pair<string, float>>>>(3);
    arraylist<pair<string, float>> Array1 = arraylist<pair<string, float>>(15);

    Array1.insert(pair("apple", 12.0f));
    Array1.insert(pair("banana", 0.8f));
    Array1.insert(pair("orange", 1.5f));
    keyFloatPairs.insert(pair("key1", Array1));
    stringhashmap<arraylist<pair<string, float>>> map = stringhashmap<arraylist<pair<string, float>>>(1);
    map.createHashTable(keyFloatPairs);
    float originalValue = map.getValue("key1").get(0).second;
    map.serialize("testdata.dat");

    stringhashmap<arraylist<pair<string, float>>>* restored = stringhashmap<arraylist<pair<string, float>>>::deserialize("testdata.dat");
    float restoredValue = (*restored).getValue("key1").get(0).second;

    ASSERT_EQ(originalValue, restoredValue);
}