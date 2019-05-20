//
//  Node.h
//  OpenGL
//
//  Created by XuRui on 2018/10/19.
//  Copyright © 2018 XuRui. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <vector>

#include "GLShaderProgram.h"

#include <GLFW/glfw3.h>

using namespace std;

class Node
{
public:
    Node();
    ~Node();
    
    static Node* create();
    
    virtual void init();
    
    virtual void visit();
    
    virtual void draw();
    
    void setShaderProgram(SHADE_PROGRAM shader);

    void addChild(Node* node);
    
    void removeChild(Node* node);
    
    void setParentNode(Node* node);
    
    void removeParentNode();
    
    void setPosition(float x, float y, float z);
    
    glm::vec3 getPosition();
    
    void setColor(glm::vec4 color);
    
    void setScale(const float x, const float y, const float z);

public:
    bool m_hasAlpha;
    
    GLShaderProgram* m_shaderProgram;
    
    vector<Node*> m_vChildrenList;
    
    Node* m_nParentNode;
    
    glm::vec3 m_fPosition;
    
    glm::vec4 m_color;
    
    glm::vec3 m_scale;
};

#endif /* Node_h */
