#include <iostream>
#include "../include/LinkedList.h"
#include "../include/fileReader.h"

int main(int argc, char const *argv[])
{
    LinkedList<int>  temp;
    temp.add(5);
    std::cout << temp.get(0) << "\n";
    std::cout << "Hello World" << "\n";
    fileReader reader = fileReader();
    reader.readFile("temp");
    return 0;
}
