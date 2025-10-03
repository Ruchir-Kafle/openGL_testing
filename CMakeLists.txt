cmake_minimum_required(VERSION 3.10)
project(OpenGLApp)

set(CMAKE_CXX_STANDARD 17)

# GLAD
include_directories(libs/glad/include)
add_library(glad src/glad.c)

# GLFW
include_directories(libs/glfw/include)
link_directories(libs/glfw/lib-vc2022)

# Executable
add_executable(OpenGLApp src/main.cpp)
target_link_libraries(OpenGLApp glad glfw3 opengl32)