#include <gtest/gtest.h>
#include "../include/arraylist.h"
using namespace std;

// Demonstrate some basic assertions.
TEST(arraylist_test, initialise)
{
  arraylist<int> list = arraylist<int>(10);
  ASSERT_EQ(list.length, 0);
  ASSERT_EQ(list.capacity, 10);
}

TEST(arraylist_test, insert)
{
  arraylist<int> list = arraylist<int>(10);
  list.insert(2);
  ASSERT_EQ(2, list.get(0));
}
TEST(arraylist_test, out_of_bounds)
{
  arraylist<int> list = arraylist<int>(10);
  ASSERT_THROW(list.get(100), out_of_range);
  ASSERT_THROW(list.remove(100), out_of_range);
  ASSERT_THROW(list.insert(10, 100), out_of_range);
}
TEST(arraylist_test, array_will_grow)
{
  arraylist<int> list = arraylist<int>(10);
  for (int i = 0; i < 102; i++)
  {
    list.insert(2);
  }
  ASSERT_EQ(list.capacity, 160);
  ASSERT_EQ(list.length, 102);
}
TEST(arraylist_test, overall_test)
{
  arraylist<int> list = arraylist<int>(7);
for (int i = 0; i < 10; i++)
  {
    list.insert(i);
  }
  ASSERT_EQ(list.capacity, 14);
  ASSERT_EQ(list.length, 10);

  ASSERT_EQ(list.get(3), 3);
  list.remove(3);
  ASSERT_EQ(list.get(8), 9);

}