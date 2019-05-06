//
//  Director.h
//  OpenGL
//
//  Created by XuRui on 2019/5/5.
//  Copyright © 2019 XuRui. All rights reserved.
//

#ifndef Director_h
#define Director_h

#include <stdio.h>

#include "../render/Node.h"
#include "../render/Camera.h"

class Director
{
public:
    Director();
    ~Director();
    
    static Director* getInstance();
    
    void drawScene();
    
    void listenerKeyBordEvent(GLFWwindow *window);
    
    void listenerMouseEvent(double posX, double posY);
    
    void listenerScrollEvent(float offsetX, float offsetY);
    
    Node* getRootNode();
    
    Camera* getMainCamera();
private:
    Node* m_rootNode;
    
    Camera* m_mainCamera;
    
    float m_pitchAngle;
    float m_yawAngle;
    float m_mouseLastX;
    float m_mouseLastY;
    
    bool m_firstMouse;
};

#endif /* Director_h */
