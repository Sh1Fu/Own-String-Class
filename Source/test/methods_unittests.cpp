#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(CheckAdditionalMethods, c_str)
{
    MyString obj("Hello");
    const char *tmp = obj.c_str();
    const char *expect = "Hello";
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
}

TEST(CheckAdditionalMethods, data)
{
    MyString obj("From ShiFu with <3");
    const char *ss = "From ShiFu with <3";
    ASSERT_STREQ(obj.c_str(), obj.data());
    EXPECT_STREQ(obj.data(), ss);
}

TEST(CheckAdditionalMethods, lenght)
{
    MyString obj("From ShiFu with <bold>LOVE</bold>");
    const char *ss = "From ShiFu with <bold>LOVE</bold>";
    ASSERT_STREQ(ss, obj.c_str());
    EXPECT_EQ(obj.lenght(), 33);
}

TEST(CheckAdditionalMethods, size)
{
    MyString obj("From ShiFu with <bold>LOVE</bold>");
    const char *ss = "From ShiFu with <bold>LOVE</bold>";
    ASSERT_STREQ(ss, obj.c_str());
    EXPECT_EQ(obj.size(), 33);
}

TEST(CheckAdditionalMethods, capacity)
{
    MyString obj("S0m3 r@nd0m S7uFf\t\t");
    const char *ss = "S0m3 r@nd0m S7uFf\t\t";
    ASSERT_STREQ(ss, obj.c_str());
    EXPECT_EQ(obj.capacity(), 20);
    obj += "12345";
    EXPECT_EQ(obj.capacity(), 32);
}

TEST(CheckAdditionalMethods, empty)
{
    MyString obj("S0m3 r@nd0m S7uFf\t\t");
    const char *ss = "S0m3 r@nd0m S7uFf\t\t";
    ASSERT_STREQ(ss, obj.c_str());
    EXPECT_FALSE(obj.empty());
    obj.clear();
    EXPECT_TRUE(obj.empty());
}

TEST(CheckAdditionalMethods, shrink_to_fit)
{
    MyString obj("INPUT string 01wdioj 2ciopej3riopjopi;");
    size_t old_capacity = obj.capacity();
    obj.shrink_to_fit();
    EXPECT_EQ(obj.capacity(), old_capacity);

    obj += "HI!";
    old_capacity = obj.capacity();
    obj.shrink_to_fit();
    ASSERT_FALSE(obj.capacity() == old_capacity);
}

TEST(CheckAdditionalMethods, clear)
{
    MyString obj("You must kill (clear) me :<");
    obj.clear();
    ASSERT_STREQ(obj.c_str(), "");
}

TEST(CheckAtMethod, at)
{
    MyString obj("ldjkfhiuwey9f823yucd89o2und98NNU9N81ND;LJK;SDJNP9U3*@)(#!*)!(@ur(*!j))");
    ASSERT_EQ('@', obj.at(52));
}

TEST(CheckIntegerConversions, to_int)
{
    MyString obj(213);
    char fobj = obj.to_int();
    ASSERT_EQ(static_cast<char>(213), (fobj));
}

TEST(CheckIntegerConversions, to_float)
{
    MyString obj(0.051231);
    float fobj = obj.to_float();
    EXPECT_EQ(static_cast<float>(0.051231), (fobj));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}