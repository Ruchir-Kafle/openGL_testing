#include "cube.h"

const GLfloat Cube::vertices[8*3] = {
    // positions
    // Front face
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    // Back face
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f
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

// Cube::Cube(const glm::vec3 color) {
//     this->color = color;
//     this->finalVertices;
    
//     for (int i = 0; i < sizeof(this->vertices) / sizeof(GLfloat); i+=3) {

//         this->finalVertices[i*2] = this->vertices[i];
//         this->finalVertices[i*2+1] = this->vertices[i+1];
//         this->finalVertices[i*2+2] = this->vertices[i+2];

//         this->finalVertices[i*2+3] = this->color.x;
//         this->finalVertices[i*2+4] = this->color.y;
//         this->finalVertices[i*2+5] = this->color.z;

//     }
// }

Cube::Cube(const std::vector<float> color) {
    this->color = color;
}