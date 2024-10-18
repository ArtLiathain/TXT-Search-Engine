#include <iostream>
#include "../include/fileReader.h"
#include "../include/mergeSort.h"
using namespace std;
int main(int argc, char const *argv[])
{
    fileReader reader = fileReader();
    arraylist<string> books = reader.getDirectories();
    mergeSort merge = mergeSort();
    for (int i = 0; i < books.length; i++){
        reader.readFile(books.get(i));
    }
    return 0;
}
