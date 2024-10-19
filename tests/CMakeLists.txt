

add_executable(
  arraylist_test
  arraylist_test.cc
  hashmap_test
  hashmap_test.cc
)
target_link_libraries(
  arraylist_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(arraylist_test)
