cmake_minimum_required(VERSION 3.10)
project(MyOpenGLApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Debug settings ----
# Enable full debug info and disable optimizations for GDB
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# ---- Add GLAD ----
add_library(glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    libs/glad/include
)

# ---- Add GLFW (prebuilt) ----
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/glfw/lib/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libs/glfw/include
)

# ---- Add your source files ----
add_executable(my_app
    src/main.cpp
    libs/shaders/shaders.cpp
)

target_include_directories(my_app PRIVATE
    libs/shaders
)

# ---- Link everything ----
target_link_libraries(my_app
    glad
    glfw
)

# ---- Windows system libs ----
if (WIN32)
    target_link_libraries(my_app
        opengl32
        gdi32
        user32
        shell32
    )
endif()
