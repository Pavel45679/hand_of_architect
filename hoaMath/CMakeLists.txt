cmake_minimum_required(VERSION 3.10)
project(hoaMath)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:DLL>")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(GLOB_RECURSE HEADERS "core/*.h")
file(GLOB_RECURSE SOURCES "core/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE hoaMath_EXPORTS)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)