cmake_minimum_required(VERSION 3.14)
project(hoaUnitTest)

enable_testing()
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS AND NOT EXISTS "${CMAKE_SOURCE_DIR}/libs/googletest-1.14.0")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/libs")
    file(DOWNLOAD
        https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        "${CMAKE_SOURCE_DIR}/libs/googletest.zip"
        SHOW_PROGRESS
    )
    file(ARCHIVE_EXTRACT
        INPUT "${CMAKE_SOURCE_DIR}/libs/googletest.zip"
        DESTINATION "${CMAKE_SOURCE_DIR}/libs"
    )
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(GTEST_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libs/googletest-1.14.0")
set(GTEST_INCLUDE_DIR "${GTEST_SOURCE_DIR}/googletest/include")

add_executable(${PROJECT_NAME}
  tests/hoaDataBase_test.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/hoaModel/core
  ${CMAKE_SOURCE_DIR}/hoaDataBase/core
  ${GTEST_INCLUDE_DIR}
)
message(STATUS "GTest source dir:  ${GTEST_INCLUDE_DIR}")
add_dependencies(${PROJECT_NAME} hoaDataBase hoaModel)

target_link_libraries(${PROJECT_NAME} PRIVATE
  hoaDataBase
  hoaModel
  gtest_main
  gtest
)

add_test(
    NAME ${PROJECT_NAME}_tests
    COMMAND ${PROJECT_NAME}_tests
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:hoaMath>
    $<TARGET_FILE:hoaModel>
    $<TARGET_FILE:hoaDataBase>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)