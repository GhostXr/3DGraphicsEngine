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
, m_hasAlpha(false)
, m_fPosition(glm::vec3(0.0f))
, m_color(glm::vec4(1.0))
, m_scale(glm::vec3(1.0))
{
}

Node::~Node()
{
    if(m_shaderProgram)
        delete m_shaderProgram;
    
    for(int i= 0; i < m_vChildrenList.size();i++)
        delete m_vChildrenList[i];
    
    m_vChildrenList.clear();
    
}

Node* Node::create()
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

void Node::setShaderProgram(SHADE_PROGRAM shader)
{
    if(m_shaderProgram != NULL)
    {
        delete m_shaderProgram;
    }
    m_shaderProgram = GLShaderProgram::createShaderProgram(shader);
}

void Node::visit()
{
    draw();
    
    if(m_vChildrenList.size() > 0)
    {
        for(int i = 0; i < m_vChildrenList.size(); i++)
        {
            m_vChildrenList[i]->visit();
        }
    }
}

void Node::draw()
{
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

glm::vec3 Node::getPosition()
{
    return m_fPosition;
}

void Node::setColor(glm::vec4 color)
{
    m_color = color;
}

void Node::setScale(const float x, const float y, const float z)
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}
