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

#include "Node.h"

class Light : public Node
{
public:
    static Light* create();
    
    Light();
    ~Light();
    
    virtual void init();
    virtual void visit();
    virtual void draw();
    virtual void blendBuff();
    
    void setLightColor(glm::vec3 color);
    
    glm::vec3 getLightColor();
    
private:
    glm::vec3 m_lightColor;
    
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};

#endif /* Light_h */
