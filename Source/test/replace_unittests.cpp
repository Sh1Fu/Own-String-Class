#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(ReplaceTests, replace_nullterminated)
{
    MyString obj = "hello amazing world";
    obj.replace(6, 7, "wonderful");
    ASSERT_STREQ(obj.c_str(), "hello wonderful world");
    obj.replace(0, 5, "Hi,");
    ASSERT_STREQ(obj.c_str(), "Hi, wonderful world");
}

TEST(ReplaceTests, replace_stdstring)
{
    MyString obj = "hello amazing world";
    std::string ss = "wonderful";
    obj.replace(6, 7, ss);
    ASSERT_STREQ(obj.c_str(), "hello wonderful world");
    ss = "ShiFu";
    obj.replace(16, 5, ss);
    ASSERT_STREQ(obj.c_str(), "hello wonderful ShiFu");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}