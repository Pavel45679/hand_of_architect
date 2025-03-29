cmake_minimum_required(VERSION 3.10)
project(hoaDataBase)

file(GLOB_RECURSE HEADERS "core/*.h")
file(GLOB_RECURSE SOURCES "core/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_link_libraries(hoaDataBase PUBLIC hoaModel)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core
							${CMAKE_SOURCE_DIR}/hoaMath/core
							${CMAKE_SOURCE_DIR}/hoaModel/core)