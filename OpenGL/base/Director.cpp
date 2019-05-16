//
//  Director.cpp
//  OpenGL
//
//  Created by XuRui on 2019/5/5.
//  Copyright © 2019 XuRui. All rights reserved.
//

#include "Director.h"

static float deltaTime = 0.0f; // 当前帧与上一帧的时间差
static float lastFrame = 0.0f; // 上一帧的时间

static Director* m_director = nullptr;
Director* Director::getInstance()
{
    if(m_director == nullptr)
    {
        m_director = new Director();
    }
    return m_director;
}

Director::Director()
:m_mouseLastX(0)
, m_mouseLastY(0)
, m_pitchAngle(0)
, m_yawAngle(-90)
, m_firstMouse(true)
, m_light(nullptr)
{
    m_rootNode = Node::create();
    m_mainCamera = new Camera();

    lastFrame = glfwGetTime();
    
    m_light = Light::create();
    m_light->setShaderProgram(LIGHT_SHADER);
    m_light->setLightColor(glm::vec3(0.3, 0.8, 0.1));
    m_light->setColor(glm::vec4(0.3, 0.8, 0.1, 1.0));
    m_light->setPosition(0, 2, 3);
    m_rootNode->addChild(m_light);
}

Director::~Director()
{
    delete m_rootNode;
    delete m_light;
    if(m_mainCamera)
        delete m_mainCamera;
}

Node* Director::getRootNode()
{
    return m_rootNode;
}

void Director::drawScene()
{
    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
    
    m_rootNode->visit();
}

void Director::listenerKeyBordEvent(GLFWwindow *window)
{
    glm::vec3 cameraPos = m_mainCamera->getCameraPos();
    glm::vec3 cameraFont = m_mainCamera->getCameraFront();
    glm::vec3 cameraUp = m_mainCamera->getCameraUp();
    float cameraSpeed = m_mainCamera->getCameraSpeed() * deltaTime;
    
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        //        blendOffset += 0.01;
        //        if(blendOffset > 1.0)
        //            blendOffset = 1.0;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        //        blendOffset -= 0.01;
        //        if(blendOffset < 0.0)
        //            blendOffset = 0.0;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFont;
        m_mainCamera->setCameraPos(cameraPos);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFont;
        m_mainCamera->setCameraPos(cameraPos);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFont, cameraUp)) * cameraSpeed;
        //        cameraPos.x -= 0.1;
        m_mainCamera->setCameraPos(cameraPos);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFont, cameraUp)) * cameraSpeed;
        //        cameraPos.x += 0.1;
        m_mainCamera->setCameraPos(cameraPos);
    }
    
}

void Director::listenerMouseEvent(double posX, double posY)
{
    if(m_firstMouse)
    {
        m_mouseLastX = posX;
        m_mouseLastY = posY;
        m_firstMouse = false;
    }
    
    float xoffset = posX - m_mouseLastX;
    float yoffset = m_mouseLastY - posY;
    m_mouseLastX = posX;
    m_mouseLastY = posY;
    
    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    m_yawAngle   += xoffset;
    m_pitchAngle += yoffset;
    
    if(m_pitchAngle > 89.0f)
        m_pitchAngle = 89.0f;
    if(m_pitchAngle < -89.0f)
        m_pitchAngle = -89.0f;
    
    glm::vec3 front = glm::vec3(1.0f);
    front.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
    front.y = sin(glm::radians(m_pitchAngle));
    front.z = cos(glm::radians(m_pitchAngle)) * sin(glm::radians(m_yawAngle));
    m_mainCamera->setCameraFront(front);
}

void Director::listenerScrollEvent(float offsetX, float offsetY)
{
    m_mainCamera->setViewFov(offsetY);
}

Camera* Director::getMainCamera()
{
    return m_mainCamera;
}

Light* Director::getLight()
{
    return m_light;
}
