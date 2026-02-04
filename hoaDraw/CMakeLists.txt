cmake_minimum_required(VERSION 3.10)
project(hoaDraw)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:DLL>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE HEADERS "core/*.h")
file(GLOB_RECURSE SOURCES "core/*.cpp")

add_executable(hoaDraw ${SOURCES} ${HEADERS})

if(WIN32)
    set_target_properties(hoaDraw PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core
								${CMAKE_SOURCE_DIR}/hoaMath/core)

target_include_directories(hoaDraw PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(hoaDraw OpenGL::GL)
