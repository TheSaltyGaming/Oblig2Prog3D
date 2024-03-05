
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <windows.h>

#include "Camera.h"
#include "FileManager.h"
#include "Mesh/Plane.h"
#include "Shader.h"
#include "Mesh/Box.h"
#include "Mesh/NPC.h"

#pragma region Public Variables

Camera MainCamera;
FileManager fileManager;
Shader shader;
//shadertest ourShader("1.model_loading.vs", "1.model_loading.fs");
Plane plane;
Plane plane1;
Box house;
Box pickup;
Box door;
Box PlayerCollision;
NPC npc;
NPC npcGraph;

Box playerinhouse;

//SCENE TWO
Box Wall1;
Box Wall2;
Box Wall3;
Box Wall4;

Box tableLeg;
Box tableTop;


std::vector<Box> walls;;
std::vector<Box> pickupList;

bool firstMouse = true; // Used in mouse_callback
bool isInsideHouse = false;

float lastX = 960, lastY = 540; //Used in mouse_callback. Set to the middle of the screen

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
int pickupcount = 0;

#pragma endregion

#pragma region Function Declarations
void setup(GLFWwindow*& window, unsigned& shaderProgram, unsigned& VBO, unsigned& VAO, unsigned& EBO,
               int& vertexColorLocation, int& value1, std::vector<float> floats);
void render(GLFWwindow* window, unsigned shaderProgram, unsigned VAO, int vertexColorLocation, std::vector<Vertex> points);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

#pragma endregion

#pragma region Settings

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

std::string vertexShaderSourceString = fileManager.readFile("VertShader.vert");
std::string fragmentShaderSourceString = fileManager.readFile("FragmentShader.frag");

const char *vertexShaderSource = vertexShaderSourceString.c_str();
const char *fragmentShaderSource = fragmentShaderSourceString.c_str();

#pragma endregion


void CreateObjects()
{
    plane.CreateMeshPlane();
    plane1.CreateMeshPlane();
    npc.CreateNPC();
    npcGraph.CreateLine();
    house = Box(1, House);
    pickup = Box(0.5f, Pickup);
    
    PlayerCollision = Box(0.7f, Player);

    playerinhouse = Box(0.2f, Player);

    //Adding walls to vector
    walls.push_back(Wall1);
    walls.push_back(Wall2);
    walls.push_back(Wall3);
    walls.push_back(Wall4);
    
    for (int i = 0; i < walls.size(); ++i)
    {
        walls[i] = Box(-4, -0.7, -0.05, 4, 3, 0.05, House);
    }

    tableLeg = Box(0.15f, Pickup);
    tableTop = Box(-0.3f, -0.05f, -0.3f, 0.3f, 0.05f, 0.3f, Npc);
    
    
    //Wall1 = Box(-1.5, -0.7, -0.05, 1.5, 1, 0.05, House);
    
    //PlayerCollision = Box(-0.1f, -0.1f, -0.1f, 0.1f, 0.2f, 0.1f, Player);

    for (int i = 0; i < 7; ++i) {
        Box pickup = Box(0.1f, Pickup);
        pickup.model = glm::translate(pickup.model, glm::vec3(i-2 * 1.5f, -0.75f, 0.0f));
        pickupList.push_back(pickup);
    }
    
    
    door = Box(-0.3, -0.7, -0.1, 0.3, 0.6, 0.1, Door);
}

int main()
{
    
    
    std::vector<Vertex> points = fileManager.readPointsFromFile("NPCPoints.txt");
    std::vector<float> floats = fileManager.convertPointsToFloats(points, 1/9.9f);
    
    GLFWwindow* window;
    unsigned shaderProgram, VBO, VAO, EBO;
    int vertexColorLocation, value1;
    
    
    setup(window, shaderProgram, VBO, VAO, EBO, vertexColorLocation, value1, floats);
    
    CreateObjects();
    
    
    render(window, shaderProgram, VAO, vertexColorLocation, points);

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


//FLytta mye setup ut av main for å gjøre det lettere å lese
//Vi kan flytte den inn igjen om du fløler det er lettere
void setup(GLFWwindow*& window, unsigned& shaderProgram, unsigned& VBO, unsigned& VAO, unsigned& EBO,
               int& vertexColorLocation, int& value1, std::vector<float> floats)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Oppgave1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        value1 = -1;
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        value1 = -1;
        return;
    }
    
    shader.CreateVertexShader(vertexShaderSource);
    shader.CreateFragmentShader(fragmentShaderSource);
    shader.LinkProgram();
    shaderProgram = shader.GetProgram();
    
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);  
    
    return;
}

void SetModelLocations()
{
    plane1.model = glm::translate(plane1.model, glm::vec3(0.0f, -8.0f, 0.0f));
    plane.model = glm::translate(plane.model, glm::vec3(0.0f, -1.2f, 0.0f));

    house.model = glm::translate(house.model, glm::vec3(4.0f, -0.2, -4.0f));
    door.model = glm::translate(house.model, glm::vec3(-0.2f, -0.299f, 1.0f));
    //house.model = glm::scale(house.model, glm::vec3(0.5f, 0.5f, 0.5f));
    npcGraph.model = glm::translate(npcGraph.model, glm::vec3(0.0f, -1, 0.0f));

    pickup.model = glm::translate(house.model, glm::vec3(1.0f, 0.599f, -1.0f));

    Wall1.model = glm::translate(Wall1.model, glm::vec3(0.0f, -7.29f, 4.0f));
    Wall2.model = glm::translate(Wall2.model, glm::vec3(0.0f, -7.29f, -4.0f));
    Wall3.model = glm::translate(Wall3.model, glm::vec3(4.0f, -7.29f, 0.0f));
    Wall4.model = glm::translate(Wall4.model, glm::vec3(-4.0f, -7.29f, 0.0f));
    
    walls[0].model = glm::rotate( Wall1.model, glm::radians(0.0001f), glm::vec3(0.1f, 0.0f, 0.0f));
    walls[1].model = glm::rotate( Wall2.model, glm::radians(0.0001f), glm::vec3(0.1f, 0.0f, 0.0f));
    walls[2].model = glm::rotate( Wall3.model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    walls[3].model = glm::rotate( Wall4.model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    tableLeg.model = glm::translate(tableLeg.model, glm::vec3(0.0f, -7.84f, 0.0f));
    tableTop.model = glm::translate(tableTop.model, glm::vec3(0.0f, -7.73f, 0.0f));

    playerinhouse.model = glm::translate(playerinhouse.model, glm::vec3(1.0f, -7.78f, -1.0f));
}

void MoveNPC(float& NpcXPos, float NpcYPos, float NpcZPos, bool isMovingForward)
{
    npc.MoveNPC( glm::vec3(NpcXPos, NpcYPos, NpcZPos));

    if (NpcXPos > 5.0f)
    {
        isMovingForward = false;
    }
    if (NpcXPos < -5.0f)
    {
        isMovingForward = true;
    }
        
    if (isMovingForward)
    {
        NpcXPos += 1 * deltaTime;
        NpcZPos = npc.f(NpcXPos);
    }
    else
    {
        NpcXPos -= 1 * deltaTime;
        NpcZPos = npc.f(NpcXPos);
    }
}

void DrawObjects(unsigned shaderProgram, std::vector<Vertex> points)
{
    glDrawArrays(GL_LINE_STRIP, 0, points.size());
    plane1.DrawPlane(shaderProgram);
    plane.DrawPlane(shaderProgram);
    npc.DrawNPC(shaderProgram);
    npcGraph.DrawLine(shaderProgram);
        
    //box.Draw(shaderProgram, 0, -1.f, 0);
    house.Draw(shaderProgram);
    pickup.Draw(shaderProgram);
    door.Draw(shaderProgram);

    tableLeg.Draw(shaderProgram);
    tableTop.Draw(shaderProgram);

    playerinhouse.Draw(shaderProgram);

    //draw all pickups
    for (int i = 0; i < pickupList.size(); ++i)
    {
        pickupList[i].Draw(shaderProgram);
    }

    for (int i = 0; i < walls.size(); ++i)
    {
        walls[i].Draw(shaderProgram);
    }
}

void CollisionCheck()
{
    for (int i = 0; i < pickupList.size(); i++)
    {
        if (PlayerCollision.CheckCollision(&pickupList[i]))
        {
            std::cout << "Collision with pickup" << std::endl;
            pickupcount++;
            std::cout << "Pickup count: " << pickupcount << std::endl;

            // Erase the pickup from the list
            pickupList.erase(pickupList.begin() + i);
            i--;
        }
    }

    if (PlayerCollision.CheckCollision(&door))
    {
        std::cout << "Collision with door" << std::endl;
        MainCamera.cameraPos = glm::vec3(3.88911f, -5.91243f, 3.82015f);
        isInsideHouse = true;
    }
}

void CameraView(unsigned shaderProgram, glm::mat4 trans, glm::mat4 projection)
{
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
    MainCamera.tick();

    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    view = glm::lookAt(MainCamera.cameraPos, MainCamera.cameraPos + MainCamera.cameraFront, MainCamera.cameraUp);
        
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
    // Pass the transformation matrix to the vertex shader
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

//Alt av rendering skjer her. Inkoudert da den while loopen
void render(GLFWwindow* window, unsigned shaderProgram, unsigned VAO, int vertexColorLocation, std::vector<Vertex> points)
{
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 projection;
    
    SetModelLocations();

    //NPC INTERPOLATION THINGS
    float NpcXPos = -5.0f;
    float NpcYPos = -0.9f;
    float NpcZPos = npc.f(NpcXPos);
    bool isMovingForward = true;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  
        
        // input
        // -----
        processInput(window);

        projection = glm::perspective(glm::radians(isInsideHouse ? 80.0f : 45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        CameraView(shaderProgram, trans, projection);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
 
        glLineWidth(12);
        
        //collision following camera
        PlayerCollision.model = glm::mat4(1.0f); // Reset the model matrix
        PlayerCollision.model = glm::translate(PlayerCollision.model, MainCamera.cameraPos);

        MoveNPC(NpcXPos, NpcYPos, NpcZPos, isMovingForward);
        
        DrawObjects(shaderProgram, points);
        
        CollisionCheck();
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{

    glm::vec3 cameraFrontXZ = glm::normalize(glm::vec3(MainCamera.cameraFront.x, 0.0f, MainCamera.cameraFront.z)); 
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    float cameraSpeed = 2.5f * deltaTime;

    if (isInsideHouse)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                playerinhouse.model =  glm::translate(playerinhouse.model,glm::vec3(-1, 0, 0)*cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            playerinhouse.model =  glm::translate(playerinhouse.model,glm::vec3(1, 0, 0)*cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            playerinhouse.model =  glm::translate(playerinhouse.model,glm::vec3(0, 0, 1)*cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            playerinhouse.model =  glm::translate(playerinhouse.model,glm::vec3(0, 0, -1)*cameraSpeed);
    }
    else
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            MainCamera.cameraPos += cameraSpeed * cameraFrontXZ;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            MainCamera.cameraPos -= cameraSpeed * cameraFrontXZ;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            MainCamera.cameraPos -= glm::normalize(glm::cross(MainCamera.cameraFront, MainCamera.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            MainCamera.cameraPos += glm::normalize(glm::cross(MainCamera.cameraFront, MainCamera.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            MainCamera.cameraPos += cameraSpeed * MainCamera.cameraUp; // Move camera up
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            MainCamera.cameraPos -= cameraSpeed * MainCamera.cameraUp; // Move camera down
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//Alt av mouse input skjer her.
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
 {
     if (isInsideHouse)
     {
         //print pitch and yaw
            //std::cout << "Pitch: " << MainCamera.pitch << " Yaw: " << MainCamera.yaw << std::endl;
         MainCamera.yaw   = -136.2;
         MainCamera.pitch = -26.6;

         glm::vec3 direction;
         direction.x = cos(glm::radians(MainCamera.yaw)) * cos(glm::radians(MainCamera.pitch));
         direction.y = sin(glm::radians(MainCamera.pitch));
         direction.z = sin(glm::radians(MainCamera.yaw)) * cos(glm::radians(MainCamera.pitch));
         MainCamera.cameraFront = glm::normalize(direction);
         return;
     }

    
     if (firstMouse)
     {
         lastX = xpos;
         lastY = ypos;
         firstMouse = false;
     }
   
     float xoffset = xpos - lastX;
     float yoffset = lastY - ypos; 
     lastX = xpos;
     lastY = ypos;
 
     float sensitivity = 0.1f;
     xoffset *= sensitivity;
     yoffset *= sensitivity;
 
     MainCamera.yaw   += xoffset;
     MainCamera.pitch += yoffset;
 
     if(MainCamera.pitch > 89.0f)
         MainCamera.pitch = 89.0f;
     if(MainCamera.pitch < -89.0f)
         MainCamera.pitch = -89.0f;
 
     glm::vec3 direction;
     direction.x = cos(glm::radians(MainCamera.yaw)) * cos(glm::radians(MainCamera.pitch));
     direction.y = sin(glm::radians(MainCamera.pitch));
     direction.z = sin(glm::radians(MainCamera.yaw)) * cos(glm::radians(MainCamera.pitch));
     MainCamera.cameraFront = glm::normalize(direction);
 }  