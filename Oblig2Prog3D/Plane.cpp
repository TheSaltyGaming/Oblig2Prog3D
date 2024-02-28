#include "Plane.h"

#include "Vertex.h"

Plane::Plane()
{
}

void Plane::CreateMeshPlane()
{
    float vertices[] = {
        // positions          // texture coords
        5.f,  5.f, 0.0f,   1.0f, 1.0f, // top right
        5.f, -5.f, 0.0f,   1.0f, 1.0f, // bottom right
       -5.f, -5.f, 0.0f,   1.0f, 1.0f, // bottom left
       -5.f,  5.f, 0.0f,   1.0f, 1.0f  // top left 
   };
    
    // std::vector<float> planeVertices = {
    //     // positions          // texture coords
    //     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0, // top right
    //     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0, // bottom right
    //    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f,1.0, // bottom left
    //    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f,1.0
    // };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
   // glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), planeVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Unbind VAO and VBO
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
   // glBindVertexArray(0);
}

void Plane::DrawPlane()
{
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, (width - 1) * (length - 1) * 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
