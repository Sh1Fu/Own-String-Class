add_subdirectory("src")

add_executable(main main.cpp)
target_link_libraries(main MyString)