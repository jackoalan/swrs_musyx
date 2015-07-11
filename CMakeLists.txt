cmake_minimum_required(VERSION 3.0)
project(swrs_musyx)

find_package(atdna REQUIRED)
atdna(DNA_dat.cpp DNA_dat.hpp)
atdna(DNA_pc.cpp DNA_pc.hpp)
include_directories(${ATHENA_INCLUDE_DIR})
add_executable(swrs_musyx DNA_dat.hpp DNA_dat.cpp DNA_pc.hpp DNA_pc.cpp main.cpp)
target_link_libraries(swrs_musyx AthenaCore)
