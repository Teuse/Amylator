cmake_minimum_required(VERSION 3.7.2)

project(Amylator)

##  --------------------------------------------------------------------------------------

set(CMAKE_SETUP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SETUP_PATH})
include(CMakeSetup)

##  --------------------------------------------------------------------------------------

add_subdirectory(libs/NetworkLib  NetworkLib-binary)
add_subdirectory(libs/ZeroconfLib ZeroconfLib-binary)
add_subdirectory(libs/GPIOLib     GPIOLib-binary)

add_subdirectory(AmylatorLib)
add_subdirectory(AmylatorServer)
add_subdirectory(Amylator)
