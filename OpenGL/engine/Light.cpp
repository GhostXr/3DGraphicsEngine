//
//  Light.cpp
//  OpenGL
//
//  Created by XuRui on 2019/5/6.
//  Copyright © 2019 XuRui. All rights reserved.
//

#include "Light.hpp"
#include "../base/Director.h"

Light* Light::create(LightType lightType)
{
    Light* light = new Light();
    if(light)
    {
        if(lightType)
            light->initByType(lightType);
        else
            light->init();
    }
    return light;
}

Light::Light()
:m_lightColor(glm::vec3(1.0))
, m_VAO(0)
, m_VBO(0)
, m_EBO(0)
, m_lightType(DIRECTION_LIGHT)
, m_lightDirction(glm::vec3(0.0, 0.5, -1.0))
, m_ambinet(glm::vec3(0.2))
, m_diffuse(glm::vec3(0.5))
, m_specular(glm::vec3(1.0))
, m_cutOff(25)
, m_epsilon(0.1)
, m_linear(0.007)
, m_quadratic(0.017)
{
}

Light::~Light()
{
}

void Light::init()
{
    
    this->blendBuff();
}

void Light::initByType(LightType lightType)
{
    this->setLightType(lightType);
    this->blendBuff();
}

void Light::blendBuff()
{
    float vertices[] = {
        //顶点                 //颜色              //纹理坐标
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // 右上
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // 左上

        0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // 右上
        0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // 左上
    };
    
    unsigned int indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3,  // 第二个三角形

        4, 5, 7, // 第一个三角形
        5, 6, 7,  // 第二个三角形

        0, 1, 4, // 第一个三角形
        1, 4, 5,  // 第二个三角形

        1, 2, 5,  // 第二个三角形
        2, 5, 6, // 第一个三角形

        2, 3, 6, // 第一个三角形
        3, 6, 7,  // 第二个三角形

        3, 4, 7, // 第一个三角形
        0, 3, 4,  // 第二个三角形
    };
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    cout<<"glBindVertexArray=="<<glGetError()<<endl;
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Light::visit()
{
    this->draw();
}

void Light::draw()
{
    m_shaderProgram->useProgram();
    
    glm::mat4 projection = Director::getInstance()->getMainCamera()->getProjection();
    
    glm::mat4 view = Director::getInstance()->getMainCamera()->getViewVector();
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 position = getPosition();
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
    //    model = glm::rotate(model, timeValue, glm::vec3(1.0f, 1.0f, 0.0f));
    
    m_shaderProgram->setUniformMat4f("projection", projection);
    m_shaderProgram->setUniformMat4f("view", view);
    m_shaderProgram->setUniformMat4f("model", model);
    
    m_shaderProgram->setUniform4f("objectColor", m_color.r, m_color.g, m_color.b, m_color.a);
    
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Light::setLightType(LightType lightType)
{
    m_lightType = lightType;
    if(lightType == DIRECTION_LIGHT)
    {
        m_quadratic = 0;
        m_linear = 0;
        m_epsilon = 0;
        m_cutOff = 0;
    }
    else if(lightType == POINT_LIGHT)
    {
        m_epsilon = 0;
        m_cutOff = 0;
        m_lightDirction = glm::vec3(0);
    }
    else if(lightType == SPOT_LIGHT)
    {
        m_quadratic = 0;
        m_linear = 0;
    }
}

LightType Light::getLightType()
{
    return m_lightType;
}
