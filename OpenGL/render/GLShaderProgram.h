//
//  GLShaderProgram.hpp
//  OpenGL
//
//  Created by XuRui on 2018/9/24.
//  Copyright © 2018年 XuRui. All rights reserved.
//

#ifndef __GLSHADERPROGRAM_H__
#define __GLSHADERPROGRAM_H__

#include <stdio.h>
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class GLShaderProgram
{
public:
    GLShaderProgram();
    
    ~GLShaderProgram();
    
    static GLShaderProgram* createShaderProgram(const GLchar* vertPath, const GLchar* fragPath);
    
    void initShaderProgram(const GLchar* vertPath, const GLchar* fragPath);
    
    void useProgram();
    
    void setUniform1i(const string &name, int value);
    void setUniform1f(const string &name, float value);
    void setUniform4f(const string &name, float value1, float value2, float value3, float value4);
    void setUniformBool(const string &name, bool value);
    void setUniformMat4f(const string &name, glm::mat4 value);
private:
    void loadShader(const char* shaderPath, string& shaderStr);
    
    unsigned int m_program;
};

#endif /* GLShader_h */
