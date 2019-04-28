//
//  main.cpp
//  OpenGL
//
//  Created by XuRui on 2018/8/29.
//  Copyright © 2018年 XuRui. All rights reserved.
//
#include <stdio.h>

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render/Node.h"

static unsigned int screenWidth = 500;
static unsigned int screenHeight = 500;
int getScreenWidth()
{
    return screenWidth;
}
int getScreenHeight()
{
    return screenHeight;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
//        blendOffset += 0.01;
//        if(blendOffset > 1.0)
//            blendOffset = 1.0;
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
//        blendOffset -= 0.01;
//        if(blendOffset < 0.0)
//            blendOffset = 0.0;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
//    printf("width == %i, height == %i", width, height);
    glViewport(0, 0, width, height);
}

void mainLoop(Node* rootNode, GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rootNode->visit();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void setOpenGLView()
{
    
}

int main(int argc, const char * argv[]) {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
//        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
//        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    setOpenGLView();
    
    Node* rootNode = Node::createNode();
    
    Node* node1 = Node::createNode();
    node1->setShaderProgram("shaders/TransformShader_vert.h", "shaders/PositionShader_frag.h");
    node1->blendBuff();
    node1->initTexture("res/textures/wall.jpg");
    node1->setPosition(1, 5, -5);
    rootNode->addChild(node1);
    
//    Node* node2 = Node::createNode();
//    node2->setShaderProgram("shaders/TransformShader_vert.h", "shaders/PositionShader_frag.h");
//    node2->blendBuff();
//    node2->initTexture("res/textures/wall.jpg");
//    node2->setPosition(0, 0, 1);
//    rootNode->addChild(node2);

//    Node* node2 = Node::createNode();
//    node2->setShaderProgram("shaders/PositionShader_vert.h", "shaders/PositionShader_frag.h");
//    node2->blendBuff();
//    node2->initTexture("res/textures/awesomeface.png");
//    rootNode->addChild(node2);
    
    mainLoop(rootNode, window);
    
    glfwTerminate();
    
    return 0;
}
