#include "MyString.hpp"
#include <iostream>

int main()
{
    MyString a(1000, 'a');
    MyString b;
    //b = "123";
    //a = b;
    a.clear();
    a.insert(3, "***", 2);
    a.insert(500, 1100, 'a');
    a.replace(0, 100, "AA");
    std::cout << a << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << a.capacity() << std::endl;
    std::cin >> b;
    std::cout << b.size() << std::endl;
}