project(cube)

set(cube_cpps
    "cube.cpp"
)

set(cube_hpps
    "matrix.hpp"
    "cube.hpp"
)

add_library(cube STATIC ${cube_cpps} ${cube_hpps})
set_property(TARGET cube PROPERTY PROJECT_LABEL "cube")
set(CUBE_LIB cube PARENT_SCOPE)
