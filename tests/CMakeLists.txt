include(GoogleTest)


add_executable(
  arraylist_test
  arraylist_test.cpp
)
target_link_libraries(
  arraylist_test
  GTest::gtest_main
)

gtest_discover_tests(arraylist_test)

add_executable(
  mergeSort_test
  mergeSort_test.cpp
  ../src/mergeSort.cpp
)



target_link_libraries(
  mergeSort_test
  GTest::gtest_main
)


gtest_discover_tests(mergeSort_test)
