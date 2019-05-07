//
//  Node.cpp
//  OpenGL
//
//  Created by XuRui on 2018/10/19.
//  Copyright © 2018 XuRui. All rights reserved.
//

#include "Node.h"
#include "Camera.h"
#include "../base/Director.h"

float blendOffset = 0.2;

Node::Node()
: m_shaderProgram(NULL)
, m_VAO(0)
, m_VBO(0)
, m_EBO(0)
, m_Texture(NULL)
, m_hasAlpha(false)
, m_fPosition(0.0f)
, m_color(glm::vec4(1.0))
{
    m_shaderProgram = GLShaderProgram::createShaderProgram(NORMAL_SHADER);
}

Node::~Node()
{
    if(m_Texture)
        delete m_Texture;
    
    if(m_shaderProgram)
        delete m_shaderProgram;
    
    for(int i= 0; i < m_vChildrenList.size();i++)
        delete m_vChildrenList[i];
    
    m_vChildrenList.clear();
    
    glBindVertexArray(0);
    
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glEnableVertexAttribArray(0);
}

Node* Node::createNode()
{
    Node* node = new Node();
    if(node)
    {
        node->init();
    }
    
    return node;
}

void Node::init()
{
}

void Node::initTexture(const char* fileName)
{
    if(m_Texture == NULL && fileName != NULL)
    {
        m_Texture = Texture::createTexture(fileName, m_hasAlpha);
    }
    
    if(m_shaderProgram)
    {
        m_shaderProgram->useProgram();
        m_shaderProgram->setUniform1i("texture", 0);
    }
}

void Node::setShaderProgram(SHADE_PROGRAM shader)
{
    if(m_shaderProgram != NULL)
    {
        delete m_shaderProgram;
    }
    m_shaderProgram = GLShaderProgram::createShaderProgram(shader);
}

void Node::blendBuff()
{
    float vertices[] = {
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   2.0f, 2.0f,   // 右上
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   2.0f, 0.0f,   // 右下
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 2.0f,    // 左上
        
        0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   2.0f, 2.0f,   // 右上
        0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   2.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 2.0f,    // 左上
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
    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Node::visit()
{
    if(m_Texture)
    {
        draw();
    }
    else
    {
        if(m_vChildrenList.size() > 0)
        {
            for(int i = 0; i < m_vChildrenList.size(); i++)
            {
                m_vChildrenList[i]->draw();
            }
        }
    }
}

void Node::draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture->getTextureID());
    //    glActiveTexture(GL_TEXTURE1);
    //    glBindTexture(GL_TEXTURE_2D, texture2->getTextureID());
    
    m_shaderProgram->useProgram();
//    float timeValue = glfwGetTime();
    //        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //        shaderProgram->setUniform4f("ourColor", 0.0f, greenValue, 0.0f, 0.0f);
//    m_shaderProgram->setUniform1f("ourPosition", sin(timeValue)*0.5);
//    m_shaderProgram->setUniform1f("blendOffset", blendOffset);
    
    glm::mat4 projection = Director::getInstance()->getMainCamera()->getProjection();
    
    glm::mat4 view = Director::getInstance()->getMainCamera()->getViewVector();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_fPosition.x, m_fPosition.y, m_fPosition.z));
//    model = glm::rotate(model, timeValue, glm::vec3(1.0f, 1.0f, 0.0f));
//    model = glm::scale(model, timeValue, glm::vec3(1.0f, 1.0f, 0.0f));
    
    m_shaderProgram->setUniformMat4f("projection", projection);
    m_shaderProgram->setUniformMat4f("view", view);
    m_shaderProgram->setUniformMat4f("model", model);

    glm::vec3 lightColor = Director::getInstance()->getLight()->getLightColor();
    m_shaderProgram->setUniform3f("lightColor", lightColor.r, lightColor.g, lightColor.b);
    
    m_shaderProgram->setUniform4f("objectColor", m_color.r, m_color.g, m_color.b, m_color.a);
    
    glBindVertexArray(m_VAO);
    //        glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Node::addChild(Node* node)
{
    if(node)
    {
        node->setParentNode(this);
        m_vChildrenList.push_back(node);
    }
}

void Node::removeChild(Node* node)
{
    if(m_vChildrenList.size() > 0)
    {
        for(vector<Node*>::iterator it = m_vChildrenList.begin(); it != m_vChildrenList.end(); it++)
        {
            if(node == *it)
            {
                node->removeParentNode();
                m_vChildrenList.erase(it);
            }
        }
    }
}

void Node::setParentNode(Node* node)
{
    if(node)
    {
        m_nParentNode = node;
    }
}

void Node::removeParentNode()
{
    m_nParentNode = NULL;
}

void Node::setPosition(float x, float y, float z)
{
    m_fPosition.x = x;
    m_fPosition.y = y;
    m_fPosition.z = z;
}

void Node::setColor(glm::vec4 color)
{
    m_color = color;
}
