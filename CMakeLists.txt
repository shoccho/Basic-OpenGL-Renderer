cmake_minimum_required(VERSION 3.10)
project(GLFW-CPP)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Find GLEW package
find_package(GLEW REQUIRED)

# Source files for the project
include_directories(include)  # Add the 'include' directory to the include paths

file(GLOB SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
set(SOURCES ${SRC})

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*;-I/include;")


# Executable
add_executable(main ${SOURCES})

# Link libraries
target_link_libraries(main PRIVATE glfw GLEW::GLEW GL)

# Copy shaders to build directory
file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/res/shaders/*.glsl")
file(COPY ${SHADERS} DESTINATION ${CMAKE_BINARY_DIR}/res/shaders)
