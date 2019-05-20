//
//  Config.h
//  OpenGL
//
//  Created by XuRui on 2019/5/20.
//  Copyright © 2019 XuRui. All rights reserved.
//

#ifndef Config_h
#define Config_h

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_FREE(p) if(p) free(p);

#define PROPERTY(varType, m_var, FuncName) private: varType m_var; public: void set##FuncName(varType var){ m_var = var; }  varType get##FuncName(void) { return m_var; }

#endif /* Config_h */
