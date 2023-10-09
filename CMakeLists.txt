cmake_minimum_required(VERSION 3.10)
project(GLFW-CPP)

# Set the path to the GLEW source code directory
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/external/glew")

# Build GLEW as a shared library
add_subdirectory(${GLEW_DIR})

# Set the path to the GLFW source code directory
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw")

# Build GLFW as a shared library
add_subdirectory(${GLFW_DIR})

# Source files for the project
include_directories(include)  

file(GLOB SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
set(SOURCES ${SRC})

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*;-I/include;")

add_definitions(-std=c++17)

# Executable
add_executable(main ${SOURCES})

# APPLE -_-
if(APPLE)
    set(libGL "-framework OpenGL")
else()
    set(libGL "GL")
endif()

# Link libraries
target_link_libraries(main libglew_static glfw ${libGL})

# Copy shaders to build directory
file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/res/shaders/*.glsl")
file(COPY ${SHADERS} DESTINATION ${CMAKE_BINARY_DIR}/res/shaders)
