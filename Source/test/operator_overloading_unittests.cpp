#include <fstream>
#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(BooleanOperators, equal)
{
    MyString obj1("HELLO"), obj2("HELLO"), obj3("NOT HEHE :<");
    EXPECT_TRUE(obj1 == obj2);
    EXPECT_FALSE(obj1 == obj3);
}

TEST(BooleanOperators, not_equal)
{
    MyString obj1("WORLD"), obj2("WORLD"), obj3("NOT HEHE AGAIN :<");
    EXPECT_FALSE(obj1 != obj2);
    EXPECT_TRUE(obj1 != obj3);
}

TEST(BooleanOperators, more_than)
{
    MyString obj1("abcd"), obj2("abce"), obj3("abcc");
    EXPECT_TRUE(obj2 > obj1);
    EXPECT_FALSE(obj3 > obj1);
}

TEST(BooleanOperators, less_than)
{
    MyString obj1("abcd"), obj2("abce"), obj3("abcc");
    EXPECT_TRUE(obj1 < obj2);
    EXPECT_FALSE(obj1 < obj3);
}

TEST(BooleanOperators, more_or_equal)
{
    MyString obj1("abcd"), obj2("abce"), obj3("abcd");
    EXPECT_TRUE(obj2 >= obj1);
    EXPECT_TRUE(obj3 >= obj1);
    EXPECT_FALSE(obj3 >= obj2);
}

TEST(BooleanOperators, less_or_equal)
{
    MyString obj1("abcd"), obj2("abce"), obj3("abcd");
    EXPECT_TRUE(obj1 <= obj2);
    EXPECT_TRUE(obj3 <= obj1);
    EXPECT_FALSE(obj2 <= obj3);
}

TEST(StreamOperators, input)
{
    std::istringstream test("Hello from input stream data flow.");
    MyString obj;
    test >> obj;
    EXPECT_STREQ(obj.c_str(), "Hello from input stream data flow.");
}

TEST(StreamOperators, output)
{
    std::ostringstream out;
    MyString obj("This string will test output stream operator overloading.");
    out << obj;
    std::string ss = out.str();
    const char *res = ss.c_str();
    EXPECT_STREQ(res, "This string will test output stream operator overloading.");
}

TEST(IndexOperator, index)
{
    MyString obj("Hello");
    ASSERT_TRUE(obj[2] == 'l');
    ASSERT_TRUE(obj[-1] == 'o');
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}