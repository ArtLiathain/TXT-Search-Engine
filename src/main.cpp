#include <iostream>
#include "../include/LinkedList.h"

int main(int argc, char const *argv[])
{
    LinkedList<int>  temp;
    temp.add(5);
    std::cout << temp.get(0) << "\n";
    std::cout << "Hello World" << "\n";
    return 0;
}
