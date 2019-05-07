//
//  Light.cpp
//  OpenGL
//
//  Created by XuRui on 2019/5/6.
//  Copyright © 2019 XuRui. All rights reserved.
//

#include "Light.hpp"

Light* Light::createLight()
{
    Light* light = new Light();
    if(light)
    {
        light->init();
    }
    return light;
}

Light::Light()
:m_lightColor(glm::vec3(1.0))
{
}

Light::~Light()
{
}

void Light::init()
{
    
}

void Light::setLightColor(glm::vec3 color)
{
    m_lightColor = color;
}

glm::vec3 Light::getLightColor()
{
    return m_lightColor;
}
