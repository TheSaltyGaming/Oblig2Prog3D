#include "NPC.h"

float NPC::f(float x)
{
    return 0.0777778*x*x*x -0.361111*x*x - 0.494445*x + 2.77778;
}

std::vector<Vertex> NPC::NPCPoints()
{
    std::vector<Vertex> NPCPoints;
    for (float i = -5; i < 5; i+=0.1)
    {   
        Vertex v;
        
        v.x = i;
        v.y = 0;
        v.z = f(i);
        NPCPoints.push_back(v);
    }
    
    return NPCPoints;
    
}

void NPC::tick()
{
    // std::cout << "Positions: " << Position.x << " " << Position.y << " "
    // << Position.z << " "<< Position.w <<std::endl;
    
}

void NPC::CreateLine()
{
    std::vector<Vertex> NPCPoints = this->NPCPoints();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, NPCPoints.size()* sizeof(Vertex), NPCPoints.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) ,(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindVertexArray(1);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*) 0);
    glEnableVertexAttribArray(0);
    
}

void NPC::DrawLine(unsigned int shaderProgram)
{
    glBindVertexArray(VAO);
    
    glDrawArrays(GL_LINES, 0, 2);
}

void NPC::GetPointsOnFile()
{
    std::vector<Vertex> NPCPoints = this->NPCPoints();
    std::ofstream file;
    file.open("NPCPoints.txt");
    for (int i = 0; i < NPCPoints.size(); i++)
    {
        file << "X: " << NPCPoints[i].x << ", " << "Y: " << NPCPoints[i].y << ", " << "Z: " << NPCPoints[i].z << ", "  << "r: "<<"1.0, "<< "g:"<<"1.0, "<< "b: "<<"0.0, " << std::endl;
    }
    file.close();
}
