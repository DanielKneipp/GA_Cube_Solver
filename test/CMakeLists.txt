project(test)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tester "test.cpp")
target_link_libraries(tester ${GTEST_BOTH_LIBRARIES} ${CUBE_LIB})
