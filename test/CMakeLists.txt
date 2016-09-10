project(test)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SRCS
    "cube_3.cpp"
    "cube_4.cpp"
    "array2d.cpp"
)

file(GLOB INSTANCES "instances/in*")

file(GLOB CONFIG_FILES "configs/*.conf")

add_executable(test_all "test_all.cpp" ${TEST_SRCS})
target_link_libraries(test_all ${GTEST_BOTH_LIBRARIES} ${CUBE_LIB})
set_property(TARGET test_all PROPERTY PROJECT_LABEL "test")

install(FILES ${INSTANCES} DESTINATION ${CMAKE_INSTALL_PREFIX}/instances)
install(FILES ${CONFIG_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/configs)
