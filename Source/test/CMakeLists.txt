project(Tests)

include(GoogleTest)
file(GLOB APP_SOURCES *.cpp)
foreach (testsourcefile ${APP_SOURCES})
    get_filename_component(testname ${testsourcefile} NAME_WLE)
    add_executable(${testname} "${testname}.cpp")
    target_link_libraries(${testname} GTest::gtest_main MyString)
    add_test(${testname} ${testname})
endforeach(file ${files})

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_SOURCE_DIR)
execute_process(
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Source/test
    COMMAND bash "-c" " cp *.in /tmp"
)
