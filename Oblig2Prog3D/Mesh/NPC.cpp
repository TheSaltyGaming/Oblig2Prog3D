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

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindVertexArray(1); 
    
}

void NPC::CreateNPC()
{
    std::vector<float> boxVertices = {
        // positions          // texture coords
        0.25f,  0.5f, 0.25f,  1.0f, 0.0f, 1.0f, // top right
        0.25f,  0.5f,-0.25f,  1.0f, 0.0f, 1.0f, // bottom right
       -0.25f,  0.5f,-0.25f,  1.0f, 0.0f, 1.0f, // bottom left
       -0.25f,  0.5f, 0.25f,  1.0f, 0.0f, 1.0f, // top left
        0.25f,  0.0f, 0.25f,  1.0f, 0.0f, 1.0f, // top right (base)
        0.25f,  0.0f,-0.25f,  1.0f, 0.0f, 1.0f, // bottom right (base)
       -0.25f,  0.0f,-0.25f,  1.0f, 0.0f, 1.0f, // bottom left (base)
       -0.25f,  0.0f, 0.25f,  1.0f, 0.0f, 1.0f, // top left (base)
    };
    unsigned int indices[] = {
        0, 1, 4, // first triangle (top face)
        1, 5, 4, // second triangle (top face)
        1, 2, 5, // third triangle (front face)
        2, 6, 5, // fourth triangle (front face)
        2, 3, 6, // fifth triangle (left face)
        3, 7, 6, // sixth triangle (left face)
        3, 0, 7, // seventh triangle (back face)
        0, 4, 7, // eighth triangle (back face)
        4, 5, 7, // ninth triangle (right face)
        5, 6, 7, // tenth triangle (right face)
        0, 1, 3, // eleventh triangle (bottom face)
        1, 2, 3  // twelfth triangle (bottom face)
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, boxVertices.size() * sizeof(float), boxVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void NPC::MoveNPC()
{
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

void NPC::DrawNPC(unsigned shaderProgram)
{
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, (width - 1) * (length - 1) * 6);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
