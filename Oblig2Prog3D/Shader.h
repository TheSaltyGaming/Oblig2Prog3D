﻿#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

public:
    void CreateVertexShader(const char* vertexShaderSource);
    void CreateFragmentShader(const char* fragmentShaderSource);
    void LinkProgram();
    unsigned int GetProgram();

    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
};