

add_executable(
  arraylist_test
  arraylist_test.cc
)
target_link_libraries(
  arraylist_test
  GTest::gtest_main
)

add_executable(
  trie_test
  trie_test.cc
  ../src/trie.cpp
)
target_link_libraries(
  trie_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(arraylist_test)
gtest_discover_tests(trie_test)
