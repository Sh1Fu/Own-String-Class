#include "../include/MyString.hpp"
#include "gtest/gtest.h"
using namespace str;

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

TEST(FindTests, find_aho)
{
    MyString a1 = "ahishers";
    std::vector<char *> strs = {"he", "she", "hers", "his"};
    std::vector<size_t> result = a1.find(strs);
    for(size_t i = 0; i < 3; i++)
    {
        EXPECT_EQ(result[i], a1.find(strs[i]) + 1);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}