include("../cmake/check_dependency.cmake")

check_dependency(core)
check_dependency(utils)

set(SRC "${PROJECT_SOURCE_DIR}/examples")
add_executable(utils_basics
    "${SRC}/utils_basics.cpp"
)

target_include_directories(utils_basics PUBLIC
    "${CROTALE_CORE_SOURCE_DIR}/include"
    "${CROTALE_UTILS_SOURCE_DIR}/include"
)

target_link_libraries(utils_basics
    crotale::core
    crotale::utils
)