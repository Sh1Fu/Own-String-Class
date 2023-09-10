#include "../include/MyString.hpp"
#include "gtest/gtest.h"

TEST(InsertTests, insert_with_char)
{
    MyString obj = "aaaaa";
    obj.insert(0, 1, '!');
    EXPECT_STREQ(obj.c_str(), "!aaaaa");
    obj.insert(3, 2, '@');
    EXPECT_STREQ(obj.c_str(), "!aa@@aaa");
}

TEST(InsertTests, insert_nullterminated)
{
    MyString obj = "aaaaa";
    obj.insert(1, "@@@@@");
    EXPECT_STREQ(obj.c_str(), "a@@@@@aaaa");
}

TEST(InsertTests, insert_part_nullterminated)
{
    MyString obj = "aaaaa";
    obj.insert(1, "@@@@@", 2);
    EXPECT_STREQ(obj.c_str(), "a@@aaaa");
}

TEST(InsertTests, insert_stdstring)
{
    std::string ss = "@@@@@";
    MyString obj = "aaaaa";
    obj.insert(1, ss);
    EXPECT_STREQ(obj.c_str(), "a@@@@@aaaa");
}

TEST(InsertTests, insert_part_stdstring)
{
    std::string ss = "@@@@@";
    MyString obj = "aaaaa";
    obj.insert(1, ss, 2);
    EXPECT_STREQ(obj.c_str(), "a@@aaaa");
}

TEST(EraseTest, erase)
{
    MyString obj("Hello World!");
    obj.erase(5, 6);
    EXPECT_STREQ(obj.c_str(), "Hello!");
}

TEST(AppendTests, append_char)
{
    MyString obj;
    obj.clear();
    obj.append(3, '!');
    EXPECT_STREQ(obj.c_str(), "!!!");
    obj.append(3, '@');
    ASSERT_STREQ(obj.c_str(), "!!!@@@");
}

TEST(AppendTests, append_nullterminated)
{
    MyString obj;
    obj.clear();
    obj.append("Hello ");
    EXPECT_STREQ(obj.c_str(), "Hello ");
    obj.append("World");
    ASSERT_STREQ(obj.c_str(), "Hello World");
}

TEST(AppendTests, append_part_nullterminated)
{
    MyString obj;
    obj.clear();
    obj.append("Hello World", 0, 6);
    EXPECT_STREQ(obj.c_str(), "Hello ");
    obj.append("Hello World", 6, 5);
    ASSERT_STREQ(obj.c_str(), "Hello World");
}

TEST(AppendTests, append_stdstring)
{
    std::string ss = "Hello ", ss2 = "world";
    MyString obj;
    obj.clear();
    obj.append(ss);
    EXPECT_STREQ(obj.c_str(), ss.c_str());
    obj.append(ss2);
    ASSERT_STREQ(obj.c_str(), "Hello world");
}

TEST(AppendTests, append_part_stdstring)
{
    std::string ss = "Hello world";
    MyString obj;
    obj.clear();
    obj.append(ss, 0, 6);
    EXPECT_STREQ(obj.c_str(), "Hello ");
    obj.append(ss, 6, 5);
    ASSERT_STREQ(obj.c_str(), "Hello world");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}