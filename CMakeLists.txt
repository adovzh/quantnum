cmake_minimum_required(VERSION 3.9)
project(quantnum)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE sources "src/*.cpp" "include/*.h")


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

find_package (Boost COMPONENTS date_time REQUIRED)
include_directories (${Boost_INCLUDE_DIR})
link_directories (/usr/local/lib ${Boost_LIBRARY_DIR})

file(GLOB_RECURSE test_sources "test/*.cpp" "test/*.h")
add_executable(runTestSuite ${test_sources})

add_dependencies(runTestSuite gtest)
include_directories("${PROJECT_SOURCE_DIR}/include" ${source_dir}/include)
target_link_libraries(runTestSuite ${binary_dir}/libgtest.a)
target_link_libraries(runTestSuite ${binary_dir}/libgtest_main.a)
target_link_libraries(runTestSuite pthread)

target_link_libraries(runTestSuite quantnum boost_date_time ${Boost_LIBRARIES})

