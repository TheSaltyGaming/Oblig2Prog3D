#include "Box.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Box::Box()
{
    
}

Box::Box(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    boxVertices = {
        // positions
        minX,  maxY,  minZ,
        minX,  minY,  minZ,
        maxX,  minY,  minZ,
        maxX,  maxY,  minZ,
        minX,  maxY,  maxZ,
        minX,  minY,  maxZ,
        maxX,  minY,  maxZ,
        maxX,  maxY,  maxZ
    };
    Setup();
}

Box::Box(float radius)
{
    minX = -radius;
    minY = -radius;
    minZ = -radius;
    maxX = radius;
    maxY = radius;
    maxZ = radius;
    boxVertices = {
        // positions
        minX,  maxY,  minZ,  1.0f, 0.0f, 1.0f,
        minX,  minY,  minZ,  1.0f, 0.0f, 1.0f,
        maxX,  minY,  minZ,  1.0f, 0.0f, 1.0f,
        maxX,  maxY,  minZ,  1.0f, 0.0f, 1.0f,
        minX,  maxY,  maxZ,  1.0f, 0.0f, 1.0f,
        minX,  minY,  maxZ,  1.0f, 0.0f, 1.0f,
        maxX,  minY,  maxZ,  1.0f, 0.0f, 1.0f,
        maxX,  maxY,  maxZ,  1.0f, 0.0f, 1.0f
    };
    Setup();
}

void Box::Setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), planeVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, boxVertices.size() * sizeof(float), boxVertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Unbind VAO and VBO
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
}

void Box::Draw(unsigned int shaderProgram)
{
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, (width - 1) * (length - 1) * 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
