#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class Cube {
    public:
        static const GLfloat vertices[8 * 3];
        static const GLuint indices[3 * 12];

        std::vector<float> color;
        GLfloat finalVertices[8 * 6];

        Cube(const std::vector<float> color);
};