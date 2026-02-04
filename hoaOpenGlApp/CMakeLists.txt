cmake_minimum_required(VERSION 3.10)
project(hoaOpenGlApp)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:DLL>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(hoaOpenGlApp ${SOURCES} ${HEADERS})

if(WIN32)
    set_target_properties(hoaOpenGlApp PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

add_dependencies(${PROJECT_NAME} hoaDraw)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
						${CMAKE_SOURCE_DIR}/hoaMath/core
						${CMAKE_SOURCE_DIR}/hoaDraw/core)

target_include_directories(hoaOpenGlApp PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(hoaOpenGlApp OpenGL::GL
						hoaDraw)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:hoaDraw>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)