cmake_minimum_required(VERSION 3.10.0)
project(Proyecto-Hotel VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Proyecto-Hotel 
    src/main.cpp
)

target_include_directories(Proyecto-Hotel PRIVATE src)