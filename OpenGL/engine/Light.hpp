//
//  Light.h
//  OpenGL
//
//  Created by XuRui on 2019/5/6.
//  Copyright © 2019 XuRui. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>

#include <glm/glm.hpp>

class Light
{
public:
    static Light* createLight();
    
    Light();
    ~Light();
    
    void init();
    
    void setLightColor(glm::vec3 color);
    
    glm::vec3 getLightColor();
    
private:
    glm::vec3 m_lightColor;
};

#endif /* Light_h */
