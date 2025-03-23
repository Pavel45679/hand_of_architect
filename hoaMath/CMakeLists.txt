cmake_minimum_required(VERSION 3.10)
project(hoaMath)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE HEADERS "core/*.h")
file(GLOB_RECURSE SOURCES "core/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)