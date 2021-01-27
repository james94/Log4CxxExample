cmake_minimum_required(VERSION 3.19)
project(TestLog4cxx)

find_package(log4cxx 0.11)
add_executable(TestLog4cxx main.cpp)
target_include_directories(TestLog4cxx PRIVATE $<TARGET_PROPERTY:log4cxx,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(TestLog4cxx PRIVATE log4cxx)

target_link_libraries(TestLog4cxx PRIVATE pthread)