

add_executable(
  arraylist_test
  arraylist_test.cc
)
target_link_libraries(
  arraylist_test
  GTest::gtest_main
)
add_executable(
  searchIndex_test
  searchIndex_test.cc
  ../src/searchIndex.cpp
  ../src/fileReader.cpp
)
target_link_libraries(
  searchIndex_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(arraylist_test)
gtest_discover_tests(searchIndex_test)
