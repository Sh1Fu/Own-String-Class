#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(ConstructorTests, Basic)
{
    MyString a1;
    EXPECT_EQ(nullptr, a1.c_str());
    EXPECT_EQ(0, a1.size());
    EXPECT_EQ(0, a1.capacity());
}
TEST(ConstructorTests, NullTerminatedString)
{
    MyString a2("Hello World!");
    const char *expect = "Hello World!";
    const char *tmp = a2.c_str();
    ASSERT_EQ(12, a2.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(13, a2.capacity());
}
TEST(ConstructorTests, ListInit)
{
    MyString a3({'h', 'e', 'l', 'l', 'o'});
    const char *expect = "hello";
    const char *tmp = a3.c_str();
    ASSERT_EQ(5, a3.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a3.capacity());
}
TEST(ConstructorTests, StringObjectInit)
{
    std::string s = "hello";
    MyString a4(s);
    const char *expect = "hello";
    const char *tmp = a4.c_str();
    ASSERT_EQ(5, a4.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a4.capacity());
}
TEST(ConstructorTests, StringPartInit)
{
    MyString a5("hello", 4);
    const char *expect = "hell";
    const char *tmp = a5.c_str();
    ASSERT_EQ(4, a5.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(5, a5.capacity());
}
TEST(ConstructorTests, MultOneSymbolInit)
{
    MyString a6(5, 'i');
    const char *expect = "iiiii";
    const char *tmp = a6.c_str();
    ASSERT_EQ(5, a6.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a6.capacity());
}
TEST(ConstructorTests, MyStringObjectInit)
{
    MyString a7("Hello");
    MyString a8(a7);
    const char *expect = "Hello";
    const char *tmp = a8.c_str();
    ASSERT_EQ(5, a8.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a8.capacity());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/*
int main(int argc, char **argv)
{
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
}*/