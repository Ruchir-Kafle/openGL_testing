#include "cube.h"

const GLfloat Cube::vertices[8*6] = {
    // positions           // colors (R, G, B)
    // Front face
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f, // 0 bottom-left
    0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f, // 1 bottom-right
    0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f, // 2 top-right
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f, // 3 top-left

    // Back face
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 4 bottom-left
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 5 bottom-right
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 6 top-right
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f  // 7 top-left
};


const GLuint Cube::indices[3*12] = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    5, 4, 7,
    7, 6, 5,

    // Left face
    4, 0, 3,
    3, 7, 4,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Top face
    3, 2, 6,
    6, 7, 3,

    // Bottom face
    4, 5, 1,
    1, 0, 4
};


Cube::Cube(const glm::vec3 position) {
    
    int j = 0;
    for (int i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
        
        int axis = 0;

        if (j == 0) {
            axis = position.x;
        } else if (j == 1) {
            axis = position.y;
        } else if (j == 2) {
            axis = position.z;
        } else {

            if (j == 5) {
                j = 0;
            } else {
                j++;
            }


            this->finalVertices[i] = vertices[i];

            continue;
        };

        j++;

        this->finalVertices[i] = vertices[i] + 1 * axis;
    }

}