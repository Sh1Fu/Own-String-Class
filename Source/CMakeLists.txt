project(OwnStringCode)

include_directories(include)
add_subdirectory(src src)
add_subdirectory(test/unittests test/unittests)
add_subdirectory(test/fuzzing test/fuzzing)
