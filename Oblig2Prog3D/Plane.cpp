#include "Plane.h"

#include "Vertex.h"

Plane::Plane()
{
}

void Plane::CreateMeshPlane()
{

    

    for (int x = 0; x < width - 1; x++) {
        for (int z = 0; z < length - 1; z++) {
            planeVertices.push_back(x);
            planeVertices.push_back(height);
            planeVertices.push_back(z);

            planeVertices.push_back(x);
            planeVertices.push_back(height);
            planeVertices.push_back(z + 1);

            planeVertices.push_back(x + 1);
            planeVertices.push_back(height);
            planeVertices.push_back(z + 1);


            planeVertices.push_back(x);
            planeVertices.push_back(height);
            planeVertices.push_back(z);

            planeVertices.push_back(x + 1);
            planeVertices.push_back(height);
            planeVertices.push_back(z);

            planeVertices.push_back(x + 1);
            planeVertices.push_back(height);
            planeVertices.push_back(z + 1);
        }
    }
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), planeVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, (width - 1) * (length - 1) * 6);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), planeVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::DrawPlane()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (width - 1) * (length - 1) * 6);
    glBindVertexArray(0);
}
