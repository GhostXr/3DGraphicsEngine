//
//  Camera.hpp
//  OpenGL
//
//  Created by XuRui on 2019/4/30.
//  Copyright © 2019 XuRui. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    
    void listenerScrollEvent();
    
    glm::mat4 getProjection();
    
    void UpdateCameraInfo();
    
    void setCameraPos(glm::vec3 cameraPos);
    
    glm::vec3 getCameraPos();
    
    glm::vec3 getCameraFront();
    
    void setCameraFront(glm::vec3 cameraFront);
    
    glm::vec3 getCameraUp();
    
    float getCameraSpeed();
    
    void setViewFov(float viewFovOffset);
    
    glm::mat4 getViewVector();
    
private:
    glm::mat4 m_m4Projection;
    glm::mat4 m_viewVector;
    
    float m_viewFov;
    
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
    float m_cameraSpeed;
    

};

#endif /* Camera_h */
