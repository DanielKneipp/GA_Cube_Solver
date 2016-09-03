project(ga)

set(ga_cpps
    "main.cpp"
    "ga.cpp"
)

set(ga_hpps
    "ga.hpp"
)

add_executable(cube_solver ${ga_cpps} ${ga_hpps})
target_link_libraries(cube_solver ${CUBE_LIB})
set_property(TARGET cube_solver PROPERTY PROJECT_LABEL "ga")
