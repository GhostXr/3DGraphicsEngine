
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

#include "base/Director.h"
#include "render/GLShaderProgram.h"

unsigned int screenWidth = 500;
unsigned int screenHeight = 500;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else
    {
        Director::getInstance()->listenerKeyBordEvent(window);
    }
}

void mouse_callback(GLFWwindow*, double offsetX, double offsetY)
{
    Director::getInstance()->listenerMouseEvent(offsetX, offsetY);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Director::getInstance()->listenerScrollEvent(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
//    printf("width == %i, height == %i", width, height);
    glViewport(0, 0, width, height);
}

void mainLoop(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Director::getInstance()->drawScene();

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
    
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    setOpenGLView();
    
    Node* rootNode = Director::getInstance()->getRootNode();
    
    Node* node1 = Node::createNode();
    node1->setShaderProgram(TRANSFORM_SHADER);
    node1->blendBuff();
    node1->initTexture("res/textures/wall.jpg");
    node1->setPosition(0, 0, -0);
    node1->setColor(glm::vec4(0.0, 0.5, 0.0, 1.0));
    rootNode->addChild(node1);

    Node* node2 = Node::createNode();
    node2->setShaderProgram(LIGHT_SHADER);
    node2->blendBuff();
    node2->initTexture("res/textures/wall.jpg");
    node2->setPosition(0, -4, -5);
    node2->setColor(glm::vec4(0.3, 0.5, 0.2, 1.0));
    rootNode->addChild(node2);

    mainLoop(window);
    
    
    glfwTerminate();
    
    return 0;
}
