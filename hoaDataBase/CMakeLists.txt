cmake_minimum_required(VERSION 3.10)
project(hoaDataBase)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:DLL>")
endif()

file(GLOB_RECURSE HEADERS "core/*.h")
file(GLOB_RECURSE SOURCES "core/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)