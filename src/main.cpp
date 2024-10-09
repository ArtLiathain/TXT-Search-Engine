#include <iostream>
#include "../include/fileReader.h"
using namespace std;
int main(int argc, char const *argv[])
{
    fileReader reader = fileReader();
    arraylist<string> books = reader.getDirectories();

    for (int i = 0; i < books.length; i++){
        reader.readFile(books.get(i));
    }
    return 0;
}
