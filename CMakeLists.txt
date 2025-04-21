cmake_minimum_required(VERSION 3.13)

project(RayTracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SUPPRESS_REGENERATION TRUE)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/external/lodepng)
include_directories(${CMAKE_SOURCE_DIR}/core/include)

file(GLOB CORE_SOURCES "${CMAKE_SOURCE_DIR}/core/src/*.cpp")
file(GLOB CORE_HEADERS "${CMAKE_SOURCE_DIR}/core/include/*.hpp")

file(GLOB LODEPNG_SOURCES "${CMAKE_SOURCE_DIR}/external/lodepng/*.cpp")
file(GLOB LODEPNG_HEADERS "${CMAKE_SOURCE_DIR}/external/lodepng/*.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
add_library(lodepng STATIC ${LODEPNG_SOURCES} ${LODEPNG_HEADERS})

add_executable(raytracer_app ${CMAKE_SOURCE_DIR}/core/main.cpp)
target_link_libraries(raytracer_app core lodepng)

set_target_properties(raytracer_app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")