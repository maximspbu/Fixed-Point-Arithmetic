cmake_minimum_required(VERSION 3.12)
project(fpa VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_VERBOSE_MAKEFILE ON)
file(GLOB SOURCES CONFIGURE_DEPENDS
    ./src/*.h
    ./src/*.cpp 
)
add_executable(fpa  ${SOURCES})
