#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Shader.h"

class Plane
{
public:
    unsigned int VBO, VAO;
    int width = 4;
    int length = 6;
    int height = 1;
    std::vector<float> planeVertices;
    Plane();

    void CreateMeshPlane();
    void DrawPlane();

};
