cmake_minimum_required(VERSION 3.10)
project(MyOpenGLApp)

set(CMAKE_CXX_STANDARD 17)

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

# ---- Your executable ----
add_executable(my_app
    src/main.cpp
)

# ---- Link everything ----
target_link_libraries(my_app
    glad
    glfw
)

# On Windows, also link system libs GLFW needs
if (WIN32)
    target_link_libraries(my_app
        opengl32
        gdi32
        user32
        shell32
    )
endif()