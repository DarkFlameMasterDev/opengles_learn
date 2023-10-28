#ifndef OPENGLES3_0_MYGLRENDERCONTEXT_H
#define OPENGLES3_0_MYGLRENDERCONTEXT_H


#include "GLES3/gl32.h"
#include "sample/SampleBase.h"

class MyGLRenderContext {

public:
    void onSurfaceCreated();

    void onSurfaceChanged(int width, int height);

    void onDrawFrame();

    void destroy();

    void destroyInstance();

    static MyGLRenderContext *getInstance();

private:
    MyGLRenderContext();

    ~MyGLRenderContext();

    static MyGLRenderContext *context;
//    SampleBase *pBeforeSample;
    SampleBase *pCurSample;
    int screenW;
    int screenH;
};


#endif //OPENGLES3_0_MYGLRENDERCONTEXT_H
