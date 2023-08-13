cmake_minimum_required(VERSION 3.10)

project(exercise_project)

set(CMAKE_RUNTIME_OUTPUTDIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

option(BUILD_TEST "build for test" ON)
option(BUILD_COVERAGE "build for coverage" OFF)

message(STATUS "build ${PROJECT_NAME}, is TEST: ${BUILD_TEST}")
message(STATUS "build ${PROJECT_NAME}, is COVERAGE: ${BUILD_COVERAGE}")

get_filename_component(THIRD_PARTY_DIR ./3rd_party ABSOLUTE)
get_filename_component(GTEST_INCLUDE ${THIRD_PARTY_DIR}/googletest/googletest/include ABSOLUTE)
get_filename_component(PROJECT_SRC ./alg ABSOLUTE)

set(CMAKE_C_FLAGS "-I ./h")

# IF (NOT DEFINED C_SECURE_DIR)
#     set(C_SECURE_DIR ${THIRD_PARTY_DIR}/libc_sec)
#     include(./cmake_utils/secure.cmake)
#     BUILD_C_SECURE(${C_SECURE_DIR})
# ENDIF()

IF (BUILD_TEST)
    set(GTEST_DIR ${THIRD_PARTY_DIR}/googletest)
    set(GTEST_MAIN ${GTEST_DIR}/googletest/src/gtest_main.cc)
    include(./cmake_utils/gtest.cmake)
    BUILD_GTEST(${GTEST_DIR})
    add_definitions(-DEXERCISE_UT)
ENDIF()

add_subdirectory(alg)
add_subdirectory(test)
