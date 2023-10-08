#ifndef OPENGLES3_0_MYGLRENDERCONTEXT_H
#define OPENGLES3_0_MYGLRENDERCONTEXT_H


#include "GLES3/gl3.h"

class MyGLRenderContext {
    MyGLRenderContext();

    ~MyGLRenderContext();

public:

    void onSurfaceCreated();

    void onSurfaceChanged(int width, int height);

    void onDrawFrame();

    void beforeDraw();

    void destroy();
    void destroyInstance();

    static MyGLRenderContext *getInstance();


private:
    static MyGLRenderContext *context;
    int screenW;
    int screenH;
    GLuint program;
    GLuint VAO, VBO;
};


#endif //OPENGLES3_0_MYGLRENDERCONTEXT_H
