﻿#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex
{
    float x, y, z, r, g, b;

    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
