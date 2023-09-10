#include "src/MyString.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    std::string s = "hello";
    MyString a1;
    MyString a2("Hello World!");
    MyString a3({'h', 'e', 'l', 'l', '5', '6', '7', '8', 's', 'd'});
    MyString a4(s);
    MyString a5("hello", 4);
    MyString a6(5, 'i');
    MyString a7(a6);

    a1 = a2 + "lol";
    a1 = a2 + a3;
    a1 = a2 + s;
    a1 = a3;
    a1 = s;
    a1 = "hello";
    a1 = '1';
    a1 += a2;
    a1 += "a2";
    a1 += s;

    const char *ss = a1.c_str();
    std::cout << ss << " " << strlen(ss) << " " << a1.size() << " " << a1.empty() << " " << a1.capacity() << std::endl;
    a1.shrink_to_fit();
    ss = a1.c_str();
    std::cout << ss << " " << strlen(ss) << " " << a1.size() << " " << a1.empty() << " " << a1.capacity() << std::endl;
    a1.clear();
    a1.shrink_to_fit();
    ss = a1.c_str();
    std::cout << ss << " " << strlen(ss) << " " << a1.size() << " " << a1.empty() << " " << a1.capacity() << std::endl;

    MyString a9;
    std::cout << "Input Test" << std::endl << "Enter smth: ";
    std::cin >> a9;
    std::cout << a9 << std::endl;

    MyString a10("aaaaa");
    a10.insert(0, 1, '!');
    std::cout << a10 << std::endl;
    a10.insert(3, 2, '@');
    std::cout << a10 << std::endl;
    a10.insert(10, 1, '@');
    std::cout << a10 << std::endl;
    a10.insert(5, "HELLO");
    std::cout << a10 << std::endl;
    a10.insert(11, "WORLD", 4);
    std::cout << a10 << std::endl;
    a10.insert(0, s);
    std::cout << a10 << std::endl;
    a10.insert(23, s, 2);
    std::cout << a10 << std::endl;
    a10.erase(0, 40);
    std::cout << a10 << std::endl;

    MyString a11;
    a11.clear();
    a11.append(3, '!');
    std::cout << a11 << std::endl;
    a11.append(3, '@');
    std::cout << a11 << std::endl;

    a11.clear();
    a11.append("Hello ");
    std::cout << a11 << std::endl;
    a11.append("World");
    std::cout << a11 << std::endl;

    std::string s1 = "hello ", s2 = "world";
    a11.clear();
    a11.append(s1);
    std::cout << a11 << std::endl;
    a11.append(s2);
    std::cout << a11 << std::endl;
    a11.append("HELLO WORLD", 0, 2);
    std::cout << a11 << std::endl;
    a11.append(s1, 4, 4);
    std::cout << a11 << std::endl;
}