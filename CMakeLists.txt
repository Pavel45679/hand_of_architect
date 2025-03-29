cmake_minimum_required(VERSION 3.10)
project(HandOfArchitect)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(hoaMath)
add_subdirectory(hoaModel)
add_subdirectory(hoaDataBase)
add_subdirectory(hoaView)
add_subdirectory(libs/googletest-1.14.0)
add_subdirectory(hoaUnitTest)