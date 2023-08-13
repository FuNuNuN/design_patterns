cmake_minimum_required(VERSION 3.10)

project(exercise_project_alg)

include_directories(${PROJECT_INCLUDE})

file(GLOB_RECURSE INCLUDES "*.h")

set(SRC 
    algs.cpp)

add_library(
    exercise_project_alg
    STATIC
    ${SRC}
)