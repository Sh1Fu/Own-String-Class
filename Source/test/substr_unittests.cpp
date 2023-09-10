#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(SubstrTests, substr_index)
{
    MyString a1 = "hello amazing world", a2;
    a2 = a1.substr(6);
    EXPECT_STREQ(a2.c_str(), "amazing world");
}

TEST(SubstrTests, substr_index_count)
{
    MyString a1 = "hello amazing world", a2;
    a2 = a1.substr(6, 7);
    EXPECT_STREQ(a2.c_str(), "amazing");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}