cmake_minimum_required(VERSION 3.10)
project(GLFW-CPP)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set the path to the GLEW source code directory
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/external/glew")

# Build GLEW as a shared library
add_subdirectory(${GLEW_DIR})

# Set the path to the GLFW source code directory
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw")

# Build GLFW as a shared library
add_subdirectory(${GLFW_DIR})

# Set GLM path
set(glm_DIR "${CMAKE_SOURCE_DIR}/external/glm")

# Build GLM as a shared library
add_subdirectory(${glm_DIR})

# Source files for the project
include_directories(include "${CMAKE_SOURCE_DIR}/src/vendor/imgui")

# not sure if we want the headers here
file(GLOB SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB IMGUI "${CMAKE_SOURCE_DIR}/src/vendor/imgui/*" )

set(SOURCES ${SRC} ${HEADERS} ${IMGUI})

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
target_link_libraries(main libglew_static glfw ${libGL}  glm::glm )