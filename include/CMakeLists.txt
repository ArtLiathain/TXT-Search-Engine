set(HEADER_FILES
    trie.h
    fileReader.h
    searchIndex.h
    hashmap.h
    mergeSort.h
    serialiseArraylist.h
    Parser.h
    arraylist.h
    initialiser.h
)
add_library(headers INTERFACE)

target_include_directories(headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})