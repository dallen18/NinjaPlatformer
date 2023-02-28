cmake_minimum_required(VERSION 3.25)
project(NinjaPlatformer)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

file(GLOB SOURCES src/*cpp)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(NinjaPlatformer ${SOURCES})

target_link_libraries(NinjaPlatformer sfml-graphics sfml-window sfml-system)
    