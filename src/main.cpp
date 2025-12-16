#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "../libs/shaders/shaders.h"
#include "cube.h"
#include "perlinNoise.h"

// Credits:
// https://learnopengl.com/Advanced-OpenGL/Instancing
// https://www.youtube.com/watch?v=45MIykWJ-C4&t=5989s

int windowWidth = 1280;
int windowHeight = 1280;

float lastMouseX = windowWidth / 2;
float lastMouseY = windowHeight / 2;  

// Camera settings    
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

const float cameraSensitivity = 0.1f;
const int cameraSpeed = 10;

double yaw = -90;
double pitch = 0;

float FOV = 75.0f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void mousePosCallback(GLFWwindow* window, double mouseX, double mouseY) {
    float deltaX = mouseX - lastMouseX;
    float deltaY = mouseY - lastMouseY;
    lastMouseX = mouseX;
    lastMouseY = mouseY;

    deltaX *= cameraSensitivity;
    deltaY *= cameraSensitivity;

    yaw += deltaX;
    pitch += deltaY;

    if (pitch > 90.0f) {
        pitch = 90.0f;
    } else if (pitch < -90.0f) {
        pitch = -90.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = -sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    Cube myCube({1.0f, 0.0f, 0.0f});
    Cube secondCube({0.0f, 0.0f, 1.0f});
    Cube thirdCube({0.0f, 1.0f, 0.0f});
    Cube fourthCube({1.0f, 1.0f, 1.0f});
    Cube fifthCube({1.0f, 1.0f, 1.0f});
    Cube myCubes[5] = {myCube, secondCube, thirdCube, fourthCube, fifthCube};

    int amountOfCubes = sizeof(myCubes)/sizeof(Cube);

    // std::vector<float> colors[sizeof(myCubes)/sizeof(Cube)] = {};

    // for (int i = 0; i < amountOfCubes; i++) {
    //     colors[i] = myCubes[i].color;
    // }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Testing", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwMakeContextCurrent(window);

    // Mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mousePosCallback);

    gladLoadGL();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Creation/generation of each buffer object
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Binding buffer objects: array, buffer, and element buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    // Setting the data the buffers will store.
    glBufferData(GL_ARRAY_BUFFER, sizeof(myCube.vertices), myCube.vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myCube.indices), myCube.indices, GL_STATIC_DRAW);

    // Inputs into the vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shaderProgram("../libs/shaders/vertexShader.vert", "../libs/shaders/fragmentShader.frag");

    glEnable(GL_DEPTH_TEST);

    // Delta time for consistency in speed/actions
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int outputSize = 128;
    float *noiseSeed = new float[outputSize * outputSize];
    int octaveCount = 1;
    float *finalNoise = new float[outputSize * outputSize];
    for (int i = 0; i < outputSize * outputSize; i++) noiseSeed[i] = (float)rand() / (float)RAND_MAX;
    
    PerlinNoise::PerlinNoise2D(outputSize, outputSize, noiseSeed, octaveCount, finalNoise);

    // std::cout << sizeof(finalNoise) << std::endl;

    bool firstPress[2] = {false, false};

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.activateShader();

        // Calculating delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Calculating camera speed using delta time so user speed doesn't depend on framerate
        GLfloat deltaTimeSpeed = cameraSpeed * deltaTime;

        // Camera movement: user interactivity
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            cameraPos += cameraFront * deltaTimeSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            cameraPos -= cameraFront * deltaTimeSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaTimeSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaTimeSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            cameraPos += cameraUp * deltaTimeSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            cameraPos -= cameraUp * deltaTimeSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            if (!firstPress[0]) {
                firstPress[0] = true;
                octaveCount++;
                if (octaveCount > 8) octaveCount = 1;
                PerlinNoise::PerlinNoise2D(outputSize, outputSize, noiseSeed, octaveCount, finalNoise);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            if (!firstPress[1]) {
                firstPress[1] = true;
                for (int i = 0; i < outputSize * outputSize; i++) noiseSeed[i] = (float)rand() / (float)RAND_MAX;
                PerlinNoise::PerlinNoise2D(outputSize, outputSize, noiseSeed, octaveCount, finalNoise);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE) {
            firstPress[0] = false;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE) {
            firstPress[1] = false;
        }

        // Set window close
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);  
        proj = glm::perspective(glm::radians(FOV), (float)windowWidth / (float)windowHeight, 0.1f, 200.0f);

        int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        int projLocation = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(VAO);
        
        for (int x = 0; x < outputSize; x++) {
            for (int z = 0; z < outputSize; z++) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, (int)(finalNoise[z * outputSize + x] * 60.0f), z));
                // std::cout << finalNoise[i] << std::endl;

                int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
                glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
                
                glDrawElements(GL_TRIANGLES, sizeof(myCube.indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
            }
        }

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shaderProgram.deleteShader();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}   