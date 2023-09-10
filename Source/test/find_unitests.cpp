#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(FindTests, find_nullterminated)
{
    MyString a1 = "hello amazing world amazing";
    int i;
    i = a1.find("amazing");
    ASSERT_TRUE(i == 6);
}

TEST(FindTests, find_nullterminated_index)
{
    MyString a1 = "hello amazing world amazing";
    int i;
    i = a1.find("amazing", 7);
    ASSERT_TRUE(i == 20);
}

TEST(FindTests, find_string)
{
    MyString a1 = "hello amazing world amazing";
    std::string ss = "amazing";
    int i;
    i = a1.find(ss);
    ASSERT_TRUE(i == 6);
}

TEST(FindTests, find_string_index)
{
    MyString a1 = "hello amazing world amazing";
    std::string ss = "amazing";
    int i;
    i = a1.find(ss, 7);
    ASSERT_TRUE(i == 20);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}