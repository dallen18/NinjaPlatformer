# cmake_minimum_required(VERSION 3.13)
# project(sfml_dino)

# set(CMAKE_CXX_STANDARD 14)
# #set(SFML_STATIC_LIBRARIES TRUE)
# #set(SFML_DIR "/home/fhaze/libs/SFML/build")
# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# find_package(SFML REQUIRED system window graphics network)
# add_executable(sfml_dino SFMLDino.cpp Player.cpp Player.h)
# target_link_libraries(sfml_dino sfml-system sfml-window sfml-graphics sfml-network)



cmake_minimum_required(VERSION 3.25)
project(NinjaPlatformer)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

file(GLOB SOURCES src/*cpp)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(NinjaPlatformer ${SOURCES})

target_link_libraries(NinjaPlatformer sfml-graphics sfml-window sfml-system)
    