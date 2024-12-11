cmake_minimum_required(VERSION 3.10)
project(AoCPlusPlus)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CURL_DIR ${CMAKE_SOURCE_DIR}/lib/curl-8.11.0)

# Find curl headers and library
include_directories(${CURL_DIR}/include include)
link_directories(
    ${CURL_DIR}/lib
)

# Add executable
add_executable(get_input_day_x helpers/get_input_day_x.cpp)
add_library(helpers helpers/helpers.cpp)
# Link against curl
target_link_libraries(get_input_day_x curl)
add_executable(day1 day1/solution.cpp helpers/helpers.cpp)
add_executable(day2 day2/solution.cpp helpers/helpers.cpp)
add_executable(day3 day3/solution.cpp helpers/helpers.cpp)
add_executable(day4 day4/solution.cpp helpers/helpers.cpp)
add_executable(day5 day5/solution.cpp helpers/helpers.cpp)
add_executable(day6 day6/solution.cpp helpers/helpers.cpp)
add_executable(day7 day7/solution.cpp helpers/helpers.cpp)
add_executable(day8 day8/solution.cpp helpers/helpers.cpp)
add_executable(day9 day9/solution.cpp helpers/helpers.cpp)
add_executable(day10 day10/solution.cpp helpers/helpers.cpp)
add_executable(day11 day11/solution.cpp helpers/helpers.cpp)
