//
//  Cube.cpp
//  OpenGL
//
//  Created by XuRui on 2019/5/8.
//  Copyright © 2019 XuRui. All rights reserved.
//

#include "Cube.hpp"

#include "../base/Director.h"

Cube* Cube::create()
{
    Cube* cube = new Cube();
    if(cube)
    {
        cube->init();
    }
    
    return cube;
}

Cube::Cube()
: m_VAO(0)
, m_VBO(0)
, m_EBO(0)
, m_Texture(NULL)
{
//    m_shaderProgram = GLShaderProgram::createShaderProgram(NORMAL_SHADER);
}

Cube::~Cube()
{
    if(m_Texture)
        delete m_Texture;
    
    glBindVertexArray(0);
    
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glEnableVertexAttribArray(0);
}

void Cube::init()
{
    this->blendBuff();
}

void Cube::setTexture(const char* fileName)
{
    if(m_Texture == NULL && fileName != NULL)
    {
        m_Texture = Texture::createTexture(fileName, m_hasAlpha);
    }
}

void Cube::blendBuff()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  0.0f,  1.0f,  0.0f
    };
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    cout<<"glBindVertexArray=="<<glGetError()<<endl;
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Cube::visit()
{
    this->draw();
}

void Cube::draw()
{
    if(m_Texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture->getTextureID());
    }
    if(m_shaderProgram)
    {
        m_shaderProgram->useProgram();
        
        m_shaderProgram->setUniform1i("texture", 0);
    }

    glm::mat4 projection = Director::getInstance()->getMainCamera()->getProjection();
    
    glm::mat4 view = Director::getInstance()->getMainCamera()->getViewVector();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_fPosition.x, m_fPosition.y, m_fPosition.z));
    //    model = glm::rotate(model, timeValue, glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(m_scale.x, m_scale.y, m_scale.z));
    
    m_shaderProgram->setUniformMat4f("projection", projection);
    m_shaderProgram->setUniformMat4f("view", view);
    m_shaderProgram->setUniformMat4f("model", model);
    
    glm::vec3 lightColor = glm::vec3(1.0);
    glm::vec3 lightPos = glm::vec3(1.0);
    Light* light = Director::getInstance()->getLight();
    if(light)
    {
        lightColor = light->getLightColor();
        lightPos = light->getPosition();
    }
    m_shaderProgram->setUniform3f("lightColor", lightColor.r, lightColor.g, lightColor.b);
    m_shaderProgram->setUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.b);
    
    glm::vec3 cameraPos = glm::vec3(0);
    Camera* camera = Director::getInstance()->getMainCamera();
    if(camera)
    {
        cameraPos = camera->getCameraPos();
    }
    m_shaderProgram->setUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
    
    m_shaderProgram->setUniform4f("objectColor", m_color.r, m_color.g, m_color.b, m_color.a);
    
    
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
}
