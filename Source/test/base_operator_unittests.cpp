#include <iostream>
#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(BaseOperatorOverloading, ObjectsConcatenate)
{
    MyString a1("World!"), a2("Hello "), a3;
    a3 = a2 + a1;
    const char *expect = "Hello World!";
    const char *tmp = a3.c_str();
    ASSERT_EQ(12, a3.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(13, a3.capacity());
}

TEST(BaseOperatorOverloading, NullTerminatedConcatenate)
{
    MyString a1, a2("Hello ");
    a1 = a2 + "World!";
    const char *expect = "Hello World!";
    const char *tmp = a1.c_str();
    ASSERT_EQ(12, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(13, a1.capacity());
}

TEST(BaseOperatorOverloading, StringObjectConcatenate)
{
    std::string s = "lo";
    MyString a1, a2("Hel");
    a1 = a2 + s;
    const char *expect = "Hello";
    const char *tmp = a1.c_str();
    ASSERT_EQ(5, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a1.capacity());
}

TEST(AssignmentOperator, WithObject)
{
    MyString a1, a2("Hello");
    a1 = a2;
    const char *expect = "Hello";
    const char *tmp = a1.c_str();
    ASSERT_EQ(5, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a1.capacity());
}

TEST(AssignmentOperator, WithStringObject)
{
    std::string s = "World";
    MyString a1;
    a1 = s;
    const char *expect = "World";
    const char *tmp = a1.c_str();
    ASSERT_EQ(5, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(6, a1.capacity());
}

TEST(AssignmentOperator, WithNullTerminated)
{
    MyString a1;
    a1 = "ShiFu;;;;;";
    const char *expect = "ShiFu;;;;;";
    const char *tmp = a1.c_str();
    ASSERT_EQ(10, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(11, a1.capacity());
}

TEST(AssignmentOperator, WithCharSym)
{
    MyString a1;
    a1 = '1';
    const char *expect = "1";
    const char *tmp = a1.c_str();
    ASSERT_EQ(1, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(2, a1.capacity());
}

TEST(AssignmentWithConcatenateOperator, WithObject)
{
    MyString a1("Hello "), a2("World");
    a1 += a2;
    const char *expect = "Hello World";
    const char *tmp = a1.c_str();
    ASSERT_EQ(11, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(16, a1.capacity());
}

TEST(AssignmentWithConcatenateOperator, WithNullTerminated)
{
    MyString a1("Hello ");
    a1 += "from ShiFu with some long string. This test also checks memory allocation and errors.";
    const char *expect = "Hello from ShiFu with some long string. This test also checks memory allocation and errors.";
    const char *tmp = a1.c_str();
    ASSERT_EQ(91, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(96, a1.capacity());
}

TEST(AssignmentWithConcatenateOperator, WithString)
{
    std::string s = "#()!@#I)!@($!#JKAHKDJASD;lk)";
    MyString a1("Hello ");
    a1 += s;
    const char *expect = "Hello #()!@#I)!@($!#JKAHKDJASD;lk)";
    const char *tmp = a1.c_str();
    ASSERT_EQ(34, a1.size());
    for (size_t i = 0; i < strlen(expect); i++)
    {
        EXPECT_EQ(expect[i], tmp[i]);
    }
    EXPECT_EQ(40, a1.capacity());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}