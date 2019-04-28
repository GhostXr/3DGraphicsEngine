//
//  Texture.cpp
//  OpenGL
//
//  Created by XuRui on 2018/10/6.
//  Copyright © 2018年 XuRui. All rights reserved.
//

#include "Texture.h"

Texture::Texture()
: m_iTextureID(0)
{
    
}

Texture::~Texture()
{
    
}

Texture* Texture::createTexture(const char* fileName, bool hasAlpha)
{
    Texture* texture = new Texture();
    if(texture)
    {
        texture->initTexture(fileName, hasAlpha);
    }
    return texture;
}

void Texture::initTexture(const char* fileName, bool hasAlpha)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
    if (data)
    {
        if(hasAlpha)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
    
    if(texture)
    {
        m_iTextureID = texture;
    }
}

unsigned int Texture::getTextureID()
{
    return m_iTextureID;
}
