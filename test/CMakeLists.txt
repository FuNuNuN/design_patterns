cmake_minimum_required(VERSION 3.10)

project(alg_ut)

include_directories(${PROJECT_INCLUDE})
include_directories(${PROJECT_SRC})
include_directories(${GTEST_INCLUDE})

set(TEST 
    algs_test.cpp)

add_executable(
    alg_ut
    ${TEST}
    ${GTEST_MAIN}
)

target_link_libraries(
    alg_ut
    exercise_project_alg
    # c_sec
    gtest
    )