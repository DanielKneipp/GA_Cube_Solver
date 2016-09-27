project(ga)

set(ga_cpps
    "main.cpp"
    "ga.cpp"
    "cube_sol.cpp"
    "cube_prob.cpp"
    "logger.cpp"
    "ga_conf.cpp"
)

set(ga_hpps
    "ga.hpp"
    "cube_sol.hpp"
    "cube_prob.hpp"
    "logger.hpp"
    "ga_conf.hpp"
    "utils.hpp"
)

add_executable(cube_ga_solver ${ga_cpps} ${ga_hpps})
target_link_libraries(cube_ga_solver ${CUBE_LIB})
set_property(TARGET cube_ga_solver PROPERTY PROJECT_LABEL "ga")

add_executable(test_solution "test_solution.cpp" "cube_prob.hpp" "cube_prob.cpp")
target_link_libraries(test_solution ${CUBE_LIB})
set_property(TARGET test_solution PROPERTY PROJECT_LABEL "solution_tester")

install(TARGETS cube_ga_solver DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS test_solution DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES plot_fit_data.gp DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES plot_ind_data.gp DESTINATION ${CMAKE_INSTALL_PREFIX})

option(USE_STATIC_SEED "Use static seed for random number generator." OFF)

if(USE_STATIC_SEED)
    add_definitions(-DUSE_STATIC_SEED)
    message(STATUS "Using STATIC seed for random number generator")
else()
    message(STATUS "Using DYNAMIC seed for random number generator")
endif()
