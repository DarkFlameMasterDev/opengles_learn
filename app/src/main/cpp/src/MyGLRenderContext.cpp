#include "MyGLRenderContext.h"
#include "android_log.h"
#include "GLUtils.h"


MyGLRenderContext *MyGLRenderContext::context = nullptr;

MyGLRenderContext::MyGLRenderContext() {

}

MyGLRenderContext::~MyGLRenderContext() {
  if (context != nullptr) {
    delete context;
    context = nullptr;
  }
}

void MyGLRenderContext::onSurfaceCreated() {
  LOGE("MyGLRenderContext::onSurfaceCreated");
  glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
}

void MyGLRenderContext::onSurfaceChanged(int width, int height) {
  LOGE("MyGLRenderContext::onSurfaceChanged [w, h] = [%d, %d]", width, height);
  glViewport(0, 0, width, height);
}


void MyGLRenderContext::beforeDraw() {
  if (program != 0) {
    return;
  }

  //1.创建着色器程序，此处将着色器程序创建封装到一个工具类中
  char vShaderStr[] =
      "#version 300 es\n"
      "layout(location = 0) in vec3 aPos;\n"
      "void main(){\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\n";

  char fShaderStr[] =
      "#version 300 es\n"
      "precision mediump float;\n"
      "out vec4 FragColor;\n"
      "void main(){\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n";

  program = GLUtils::CreateProgram(vShaderStr, fShaderStr);

  //2.生成VAO,VBO对象,并绑定顶点属性
  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //顶点坐标属性
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) nullptr);
  glEnableVertexAttribArray(0);

  glBindVertexArray(GL_NONE);
  glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
 glBindVertexArray(GL_NONE);
}


void MyGLRenderContext::onDrawFrame() {
  beforeDraw();
  if (program == 0) {
    return;
  }
  //清除buffer
  glClearColor(0.3f, 0.5f, 0.4f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  //使用程序着色器对象
  glUseProgram(program);
  //绑定VAO
  glBindVertexArray(VAO);
  //开始绘制
  glDrawArrays(GL_TRIANGLES, 0, 3);
  //解绑VAO
  glBindVertexArray(GL_NONE);
  //解绑程序着色器对象
//  glUseProgram(GL_NONE);
}

MyGLRenderContext *MyGLRenderContext::getInstance() {
  if (context == nullptr) {
    context = new MyGLRenderContext();
  }
  return context;
}


void MyGLRenderContext::destroyInstance() {
  LOGE("MyGLRenderContext::destroyInstance");
  if (program) {
    delete context;
    context = nullptr;
  }
}

void MyGLRenderContext::destroy() {
  if (program) {
    program = GL_NONE;
  }
  glDeleteVertexArrays(1, &VAO);
  destroyInstance();
}
