//
//  Camera.cpp
//  OpenGL
//
//  Created by XuRui on 2019/4/30.
//  Copyright © 2019 XuRui. All rights reserved.
//

#include "Camera.h"

Camera::Camera()
:m_m4Projection(glm::mat4(1.0))
, m_viewFov(45.0)
, m_cameraPos(glm::vec3(0.0f, 0.0f, 20.0f))
, m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
, m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
, m_cameraSpeed(1.5)
, m_viewVector(glm::mat4(1.0))
{
    UpdateCameraInfo();
}

Camera::~Camera()
{
    
}

void Camera::UpdateCameraInfo()
{
    m_m4Projection = glm::perspective(glm::radians(m_viewFov), 500.0f / 500.0f, 0.1f, 100.0f);
    
    m_viewVector = glm::lookAt(getCameraPos(), getCameraPos() + getCameraFront(), getCameraUp());
}

glm::mat4 Camera::getProjection()
{
    return m_m4Projection;
}

void Camera::setViewFov(float viewFovOffset)
{
    if(m_viewFov >= 1.0f && m_viewFov <= 45.0f)
        m_viewFov -= viewFovOffset;
    if(m_viewFov <= 1.0f)
        m_viewFov = 1.0f;
    if(m_viewFov >= 45.0f)
        m_viewFov = 45.0f;
    
    UpdateCameraInfo();
}

void Camera::setCameraPos(glm::vec3 cameraPos)
{
    m_cameraPos = cameraPos;
    
    UpdateCameraInfo();
}

glm::vec3 Camera::getCameraPos()
{
    return m_cameraPos;
}

glm::vec3 Camera::getCameraFront()
{
    return m_cameraFront;
}

void Camera::setCameraFront(glm::vec3 cameraFront)
{
    m_cameraFront = cameraFront;
}

glm::vec3 Camera::getCameraUp()
{
    return m_cameraUp;
}

float Camera::getCameraSpeed()
{
    return m_cameraSpeed;
}

glm::mat4 Camera::getViewVector()
{
    return m_viewVector;
}
