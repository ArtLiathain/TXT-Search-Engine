set(HEADER_FILES
    LinkedList.h
    fileReader.h
    hashmap.h
)
add_library(headers INTERFACE)
target_include_directories(headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})