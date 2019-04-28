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

#include "Texture.h"
#include "GLShaderProgram.h"

#include <GLFW/glfw3.h>

using namespace std;

class Node
{
public:
    Node();
    ~Node();
    
    static Node* createNode();
    
    void init();
    
    void initTexture(const char* fileName);
    
    void setShaderProgram(const char* vertShaderName, const char* fragShaderName);
    
    void visit();
    
    void draw();

    void addChild(Node* node);
    
    void removeChild(Node* node);
    
    void setParentNode(Node* node);
    
    void removeParentNode();
    
    void setPosition(float x, float y, float z);
    
    void blendBuff();
    
private:
    Texture* m_Texture;
    
    bool m_hasAlpha;
    
    GLShaderProgram* m_shaderProgram;
    
    vector<Node*> m_vChildrenList;
    
    Node* m_nParentNode;
    
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
    
    glm::vec3 m_fPosition;
};

#endif /* Node_h */
