cmake_minimum_required(VERSION 3.10...3.30)

# set the project name
project(WolfiBreakout)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# add executable
file(GLOB SOURCES "*.cpp")
add_executable(WolfiBreakout ${SOURCES})

# specify required libraries
target_link_libraries(WolfiBreakout astu astu_box2d)
