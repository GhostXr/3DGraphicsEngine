//
//  Cube.cpp
//  OpenGL
//
//  Created by XuRui on 2019/5/8.
//  Copyright © 2019 XuRui. All rights reserved.
//

#include "Cube.hpp"

#include <string>

#include "../base/Director.h"
#include "../Config.h"

using namespace std;

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
, m_specularTexture(NULL)
{
//    m_shaderProgram = GLShaderProgram::createShaderProgram(NORMAL_SHADER);
}

Cube::~Cube()
{
    SAFE_FREE(m_Texture);
    SAFE_FREE(m_specularTexture);
    
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
        bool hasAlpha = false;
        if(strstr(fileName, ".png"))
        {
            hasAlpha = true;
        }
        m_Texture = Texture::createTexture(fileName, hasAlpha);
    }
}


void Cube::setSpecularTexture(const char* fileName)
{
    if(m_specularTexture == NULL && fileName != NULL)
    {
        bool hasAlpha = false;
        if(strstr(fileName, ".png"))
        {
            hasAlpha = true;
        }
        m_specularTexture = Texture::createTexture(fileName, hasAlpha);
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
    
    if(m_specularTexture)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_specularTexture->getTextureID());
    }
    if(m_shaderProgram)
    {
        m_shaderProgram->useProgram();
        
        m_shaderProgram->setUniform1i("texture", 0);
        
        m_shaderProgram->setUniform1i("texture", 1);
    }

    glm::mat4 projection = Director::getInstance()->getMainCamera()->getProjection();
    
    glm::mat4 view = Director::getInstance()->getMainCamera()->getViewVector();
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 position = getPosition();
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
    //    model = glm::rotate(model, timeValue, glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(m_scale.x, m_scale.y, m_scale.z));
    
    m_shaderProgram->setUniformMat4f("projection", projection);
    m_shaderProgram->setUniformMat4f("view", view);
    m_shaderProgram->setUniformMat4f("model", model);
    
    glm::vec3 lightColor = glm::vec3(1.0);
    glm::vec3 lightPos = glm::vec3(1.0);
    glm::vec3 lightDirc = glm::vec3(-1.0);
    glm::vec3 lightAmbinet = glm::vec3(0.0);
    glm::vec3 lightDifuse = glm::vec3(0.0);
    glm::vec3 lightSpecular = glm::vec3(0.0);
    float cutOff = 0;
    float epsilon = 0;
    float linear = 0;
    float quadratic = 0;
    LightType lightType = DIRECTION_LIGHT;
    
    Light* light = Director::getInstance()->getLight();
    if(light)
    {
        lightColor = light->getLightColor();
        lightPos = light->getPosition();
        lightDirc = light->getLightDirction();
        lightAmbinet = light->getLightAmbinet();
        lightDifuse = light->getLightDiffuse();
        lightSpecular = light->getLightSpecular();
        cutOff = light->getSpotLightCutOff();
        epsilon = light->getSpotLightEpsilon();
        linear = light->getPointLightLinear();
        quadratic = light->getPointLightQuadratic();
        lightType = light->getLightType();
    }
    
    if(lightType == DIRECTION_LIGHT)
    {
        m_shaderProgram->setUniform3f("directionLight.ambinet", lightAmbinet.x, lightAmbinet.y, lightAmbinet.z);
        m_shaderProgram->setUniform3f("directionLight.diffuse", lightDifuse.x, lightDifuse.y, lightDifuse.z);
        m_shaderProgram->setUniform3f("directionLight.specular", lightSpecular.x, lightSpecular.y, lightSpecular.z);
        m_shaderProgram->setUniform3f("directionLight.direction", lightDirc.x, lightDirc.y, lightDirc.z);
    }
    
    //点光源
    if(lightType == POINT_LIGHT)
    {
        m_shaderProgram->setUniform3f("pointLight.ambinet", lightAmbinet.x, lightAmbinet.y, lightAmbinet.z);
        m_shaderProgram->setUniform3f("pointLight.diffuse", lightDifuse.x, lightDifuse.y, lightDifuse.z);
        m_shaderProgram->setUniform3f("pointLight.specular", lightSpecular.x, lightSpecular.y, lightSpecular.z);
        m_shaderProgram->setUniform3f("pointLight.position", lightPos.x, lightPos.y, lightPos.z);
        m_shaderProgram->setUniform1f("pointLight.linear", linear);
        m_shaderProgram->setUniform1f("pointLight.quadratic", quadratic);
    }
    
    //切光角
    if(lightType == SPOT_LIGHT)
    {
        m_shaderProgram->setUniform3f("spotLight.ambinet", lightAmbinet.x, lightAmbinet.y, lightAmbinet.z);
        m_shaderProgram->setUniform3f("spotLight.diffuse", lightDifuse.x, lightDifuse.y, lightDifuse.z);
        m_shaderProgram->setUniform3f("spotLight.specular", lightSpecular.x, lightSpecular.y, lightSpecular.z);
        m_shaderProgram->setUniform3f("spotLight.position", lightPos.x, lightPos.y, lightPos.z);
        m_shaderProgram->setUniform3f("spotLight.direction", lightDirc.x, lightDirc.y, lightDirc.z);
        m_shaderProgram->setUniform1f("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
        m_shaderProgram->setUniform1f("spotLight.epsilon", epsilon);
    }
    
    
    glm::vec3 cameraPos = glm::vec3(0);
    Camera* camera = Director::getInstance()->getMainCamera();
    if(camera)
    {
        cameraPos = camera->getCameraPos();
    }
    m_shaderProgram->setUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
    
    m_shaderProgram->setUniform4f("objectColor", m_color.r, m_color.g, m_color.b, m_color.a);
    
//    m_shaderProgram->setUniform3f("material.ambinet", 0.5, 0.5, 0.5);
//    m_shaderProgram->setUniform3f("material.diffuse", 0.5, 0.5, 0.5);
//    m_shaderProgram->setUniform3f("material.specular", 0.5, 0.5, 0.5);
    m_shaderProgram->setUniform1i("material.diffuse", 0);
    m_shaderProgram->setUniform1i("material.specular", 1);
    m_shaderProgram->setUniform1f("material.shininess", 32.0);
    
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
}
