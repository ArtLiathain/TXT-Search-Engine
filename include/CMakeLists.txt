set(HEADER_FILES
    LinkedList.h
    trie.h
    fileReader.h
    searchIndex.h
    hashmap.h
    mergeSort.h
)
add_library(headers INTERFACE)

target_include_directories(headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})