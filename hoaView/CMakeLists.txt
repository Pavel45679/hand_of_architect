cmake_minimum_required(VERSION 3.10)
project(hoaView)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} hoaModel)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/hoaModel/core
    ${CMAKE_SOURCE_DIR}/hoaMath/core
	${CMAKE_SOURCE_DIR}/hoaDataBase/core
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:hoaMath>
    $<TARGET_FILE:hoaModel>
	$<TARGET_FILE:hoaDataBase>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)