set(SOURCE_FILES
    main.cpp
    mergeSort.cpp
    fileReader.cpp
)
add_executable(my_executable ${SOURCE_FILES})

target_link_libraries(my_executable headers)