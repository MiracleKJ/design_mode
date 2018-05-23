cmake_minimum_required(VERSION 3.8)
project(design_mode)

set(CMAKE_CXX_STANDARD 17)
set(out_name main.o)

set(source_files ./main.cpp)
add_executable(${out_name} ${source_files})
