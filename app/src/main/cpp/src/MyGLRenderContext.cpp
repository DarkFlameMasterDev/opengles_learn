#include "MyGLRenderContext.h"
#include "log_utils.h"
#include "GLUtils.h"
#include "sample/SampleTriangle.h"
#include "sample/SampleSquare.h"
#include "sample/SampleTexture.h"


MyGLRenderContext *MyGLRenderContext::context = nullptr;

MyGLRenderContext::MyGLRenderContext() {
  pCurSample = new (SampleTexture);
}

MyGLRenderContext::~MyGLRenderContext() {
  if (context != nullptr) {
    delete context;
    context = nullptr;
  }

  if (pCurSample) {
    delete pCurSample;
    pCurSample = nullptr;
  }

//  if (pBeforeSample) {
//    delete pBeforeSample;
//    pBeforeSample = nullptr;
//  }
}

void MyGLRenderContext::onSurfaceCreated() {
  LOGE("MyGLRenderContext::onSurfaceCreated");
  glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
}

void MyGLRenderContext::onSurfaceChanged(int width, int height) {
  LOGE("MyGLRenderContext::onSurfaceChanged [w, h] = [%d, %d]", width, height);
  glViewport(0, 0, width, height);
}


void MyGLRenderContext::onDrawFrame() {
  pCurSample->beforeDraw(screenW, screenH);
  pCurSample->draw();
}

MyGLRenderContext *MyGLRenderContext::getInstance() {
  if (context == nullptr) {
    context = new MyGLRenderContext();
  }
  return context;
}


void MyGLRenderContext::destroyInstance() {
  LOGE("MyGLRenderContext::destroyInstance");
  if (context) {
    delete context;
    context = nullptr;
  }
}

void MyGLRenderContext::destroy() {
  pCurSample->destroy();
  destroyInstance();
}
