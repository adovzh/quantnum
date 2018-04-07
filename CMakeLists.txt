cmake_minimum_required(VERSION 3.10)
project(quantnum)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources "src/*.cpp" "include/*.h")


add_library(quantnum ${sources})

##################################
# Download and install GoogleTest

include(ExternalProject)
ExternalProject_Add(gtest
        URL https://github.com/google/googletest/archive/release-1.7.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND ""
        )
ExternalProject_Get_Property(gtest source_dir binary_dir)

add_executable(runTestSuite test/testSuite.cpp)

add_dependencies(runTestSuite gtest)
include_directories("${PROJECT_SOURCE_DIR}/include" ${source_dir}/include)
target_link_libraries(runTestSuite ${binary_dir}/libgtest.a)
target_link_libraries(runTestSuite ${binary_dir}/libgtest_main.a)

target_link_libraries(runTestSuite quantnum)