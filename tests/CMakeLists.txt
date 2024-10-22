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
  hashmap_test
  hashmap_test.cpp
  ../src/serialiseArraylist.cpp
)
target_link_libraries(
  hashmap_test
  GTest::gtest_main
)

gtest_discover_tests(hashmap_test)

add_executable(
  trie_test
  trie_test.cc
  ../src/trie.cpp
)
target_link_libraries(
  trie_test
  GTest::gtest_main
)

gtest_discover_tests(trie_test)

add_executable(
  searchIndex_test
  searchIndex_test.cc
  ../src/searchIndex.cpp
  ../src/fileReader.cpp
  ../src/trie.cpp
  ../src/mergeSort.cpp
)
target_link_libraries(
  searchIndex_test
  GTest::gtest_main
)
gtest_discover_tests(searchIndex_test)


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
