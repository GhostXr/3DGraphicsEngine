//
//  Cube.hpp
//  OpenGL
//
//  Created by XuRui on 2019/5/8.
//  Copyright © 2019 XuRui. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>

#include "Node.h"
#include "Texture.h"

class Cube : public Node
{
public:
    static Cube* create();
    
    Cube();
    ~Cube();
    
    virtual void init();
    virtual void visit();
    virtual void draw();
    
    void setTexture(const char* fileName);
    
    void setSpecularTexture(const char* fileName);
    
    virtual void blendBuff();
    
    Texture* m_Texture;
    
    Texture* m_specularTexture;
    
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};

#endif /* Cube_hpp */
