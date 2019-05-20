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
#include "../Config.h"

enum LightType
{
    DIRECTION_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT
};

class Light : public Node
{
public:
    static Light* create(LightType lightType);
    
    Light();
    ~Light();
    
    virtual void init();
    void initByType(LightType lightType);
    virtual void visit();
    virtual void draw();
    virtual void blendBuff();
    
    void setLightType(LightType lightType);
    
    LightType getLightType();
    
    PROPERTY(glm::vec3, m_lightColor, LightColor);
    
    PROPERTY(glm::vec3, m_lightDirction, LightDirction);
    
    PROPERTY(glm::vec3, m_ambinet, LightAmbinet);
    
    PROPERTY(glm::vec3, m_diffuse, LightDiffuse);
    
    PROPERTY(glm::vec3, m_specular, LightSpecular);
    
    PROPERTY(float, m_cutOff, SpotLightCutOff);
    
    PROPERTY(float, m_epsilon, SpotLightEpsilon);
    
    PROPERTY(float, m_linear, PointLightLinear);
    
    PROPERTY(float, m_quadratic, PointLightQuadratic);
private:
    
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
    
    LightType m_lightType;
};

#endif /* Light_h */
