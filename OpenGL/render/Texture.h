//
//  Texture.h
//  OpenGL
//
//  Created by XuRui on 2018/10/6.
//  Copyright © 2018年 XuRui. All rights reserved.
//

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "../external/stb_image.h"

using namespace std;

class Texture
{
public:
    Texture();
    ~Texture();
    
    static Texture* createTexture(const char* fileName, bool hasAlpha);
    
    void initTexture(const char* fileName, bool hasAlpha);
    
    unsigned int getTextureID();
    
private:
    unsigned int m_iTextureID;
};

#endif /* Texture_h */
