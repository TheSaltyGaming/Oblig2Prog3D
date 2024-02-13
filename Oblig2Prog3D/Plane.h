#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"

class Plane
{
public:
    float width;
    float height;
    glm::vec3 position;
    glm::vec3 color;

    Plane(float width, float height, glm::vec3 position, glm::vec3 color)
        : width(width), height(height), position(position), color(color) {}

    void draw(Shader& shader);

};
