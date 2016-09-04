project(test)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SRCS
    "cube_3.cpp"
    "array2d.cpp"
)

set(TEST_ASSETS
    "in_test_3"
)

add_executable(test_all "test_all.cpp" ${TEST_SRCS})
target_link_libraries(test_all ${GTEST_BOTH_LIBRARIES} ${CUBE_LIB})
set_property(TARGET test_all PROPERTY PROJECT_LABEL "test")

file(COPY ${TEST_ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
