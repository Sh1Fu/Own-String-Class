#include <vector>
#include "../include/MyString.hpp"
#include "gtest/gtest.h"
using namespace str;

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
    ASSERT_STREQ(expect, tmp);
    EXPECT_EQ(13, a2.capacity());
}
TEST(ConstructorTests, ListInit)
{
    MyString a3({'h', 'e', 'l', 'l', 'o'});
    const char *expect = "hello";
    const char *tmp = a3.c_str();
    ASSERT_EQ(5, a3.size());
    ASSERT_STREQ(expect, tmp);
    EXPECT_EQ(6, a3.capacity());
}
TEST(ConstructorTests, StringObjectInit)
{
    std::string s = "hello";
    MyString a4(s);
    const char *expect = "hello";
    const char *tmp = a4.c_str();
    ASSERT_EQ(5, a4.size());
    ASSERT_STREQ(expect, tmp);
    EXPECT_EQ(6, a4.capacity());
}
TEST(ConstructorTests, StringPartInit)
{
    MyString a5("hello", 4);
    const char *expect = "hell";
    const char *tmp = a5.c_str();
    ASSERT_EQ(4, a5.size());
    ASSERT_STREQ(expect, tmp);
    EXPECT_EQ(5, a5.capacity());
}
TEST(ConstructorTests, MultOneSymbolInit)
{
    MyString a6(5, 'i');
    const char *expect = "iiiii";
    const char *tmp = a6.c_str();
    ASSERT_EQ(5, a6.size());
    ASSERT_STREQ(expect, tmp);
    EXPECT_EQ(6, a6.capacity());
}
TEST(ConstructorTests, MyStringObjectInit)
{
    MyString a7("Hello");
    MyString a8(a7);
    const char *expect = "Hello";
    const char *tmp = a8.c_str();
    ASSERT_EQ(5, a8.size());
    ASSERT_STREQ(expect, tmp);
    EXPECT_EQ(6, a8.capacity());
}

TEST(ConstructorTests, InitByInt)
{
    MyString a7(123);
    ASSERT_STREQ("123", a7.c_str());
}

TEST(ConstructorTests, InitByDouble)
{
    MyString obj(0.05);
    ASSERT_STREQ("0.05", obj.c_str());
}

TEST(ConstructorTests, MoveConstructor)
{
    std::vector<MyString> vec;
    MyString obj2("World");
    vec.push_back(MyString("Hello"));
    EXPECT_EQ(vec[0].size(), 5);
    EXPECT_EQ(vec[0].capacity(), 6);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}