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

install(TARGETS cube_ga_solver DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES plotGAData.gp DESTINATION ${CMAKE_INSTALL_PREFIX})
