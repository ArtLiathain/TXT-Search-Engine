set(SOURCE_FILES
    main.cpp
    trie.cpp
    fileReader.cpp
    mergeSort.cpp
    searchIndex.cpp
    serialiseArraylist.cpp
    Parser.cpp
)
add_executable(my_executable ${SOURCE_FILES})

target_link_libraries(my_executable headers)