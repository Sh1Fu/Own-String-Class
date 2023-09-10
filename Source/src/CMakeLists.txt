project(MyStringClass)
add_library(MyString STATIC MyString.cpp)
target_include_directories(MyString PUBLIC include)