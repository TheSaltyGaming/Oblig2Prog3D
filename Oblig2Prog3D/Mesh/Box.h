#pragma once
#include <vector>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Box
{
public:
    Box();
    Box(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    Box(float radius);
    float minX, minY, minZ, maxX, maxY, maxZ;
    std::vector<float> boxVertices;

    unsigned int indices[36] = {
        0, 1, 3, // first triangle (top face)
        1, 2, 3, // second triangle (top face)
        4, 5, 7, // third triangle (bottom face)
        5, 6, 7, // fourth triangle (bottom face)
        0, 1, 5, // fifth triangle (front face)
        0, 5, 4, // sixth triangle (front face)
        3, 2, 6, // seventh triangle (back face)
        3, 6, 7, // eighth triangle (back face)
        0, 3, 7, // ninth triangle (left face)
        0, 7, 4, // tenth triangle (left face)
        1, 2, 6, // eleventh triangle (right face)
        1, 6, 5  // twelfth triangle (right face)
    };
    unsigned int VBO, VAO, EBO;

    glm::mat4 model = glm::mat4(1.0f);

    //setup
    void Setup();
    
    
    void Draw(unsigned int shaderProgram);
    void Draw(float x, float y, float z);
    void Draw(float x, float y, float z, float scale);
    
};
