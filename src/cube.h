#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cube {
    public:
        static const GLfloat vertices[8 * 6];
        static const GLuint indices[3 * 12];
        GLfloat finalVertices[8 * 6];

        // Cube(const glm::vec3 position);
};