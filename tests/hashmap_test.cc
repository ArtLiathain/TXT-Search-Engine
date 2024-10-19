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
    ASSERT_FALSE(hashmap.getValue("Test") == 42);
}

TEST(hashmap_test, insertAndRemove)
{
    stringhashmap<int> hashmap = stringhashmap<int>(2);
    hashmap.insert("Test1", 42);
    ASSERT_EQ(hashmap.getValue("Test1"), 42);
    hashmap.remove("Test1");
    ASSERT_FALSE(hashmap.getValue("Test1") == 42);
}