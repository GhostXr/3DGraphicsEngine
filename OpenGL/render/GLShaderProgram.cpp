//
//  GLShader.cpp
//  OpenGL
//
//  Created by XuRui on 2018/9/24.
//  Copyright © 2018年 XuRui. All rights reserved.
//

#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram()
: m_program(NULL)
{
    
}

GLShaderProgram::~GLShaderProgram()
{
    glDeleteProgram(m_program);
    m_program = NULL;
}

GLShaderProgram* GLShaderProgram::createShaderProgram(const GLchar* vertPath, const GLchar* fragPath)
{
    GLShaderProgram* program = new GLShaderProgram();
    if(program)
    {
        program->initShaderProgram(vertPath, fragPath);
    }
    return program;
}

void GLShaderProgram::initShaderProgram(const GLchar* vertPath, const GLchar* fragPath)
{
    string vertexShaderStr, fragShaderStr;
    loadShader(vertPath, vertexShaderStr);
    loadShader(fragPath, fragShaderStr);
    const char* vertexShaderSource = vertexShaderStr.c_str();
    const char* fragmentShaderSource = fragShaderStr.c_str();
    
    int  success;
    char infoLog[512];
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(! success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(! success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::LINKED_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GLShaderProgram::loadShader(const char *shaderPath, string& shaderStr)
{
    string shaderCode;
    ifstream shaderFile;
    
    shaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        shaderFile.open(shaderPath);
        
        stringstream shaderStrem;
        shaderStrem << shaderFile.rdbuf();
        shaderFile.close();
        
        shaderStr = shaderStrem.str();
        
    } catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
}

void GLShaderProgram::useProgram()
{
    glUseProgram(m_program);
}

void GLShaderProgram::setUniform1i(const string &name, int value)
{
    int vertexColorLocation = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(vertexColorLocation, value);
}

void GLShaderProgram::setUniform1f(const string &name, float value)
{
    int vertexColorLocation = glGetUniformLocation(m_program, name.c_str());
    glUniform1f(vertexColorLocation, value);
}

void GLShaderProgram::setUniform4f(const string &name, float value1, float value2, float value3, float value4)
{
    int vertexColorLocation = glGetUniformLocation(m_program, name.c_str());
    glUniform4f(vertexColorLocation, value1, value2, value3, value4);
}

void GLShaderProgram::setUniformBool(const string &name, bool value)
{
    int vertexColorLocation = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(vertexColorLocation, (int)value);
}

void GLShaderProgram::setUniformMat4f(const string &name, glm::mat4 value)
{
    int vertexColorLocation = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(value));
}
