#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cerrno>


std::string getFileContents(const char *filename);

class Shader
{
    public:
        GLuint ID;

        Shader(const char *vertexFile, const char *fragmentFile);
        
        void activateShader();
        void deleteShader();

};
