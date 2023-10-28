//
// Created by 曹璐韬 on 2023/10/8.
//

#include "SampleTriangle.h"
#include "GLUtils.h"
#include "log_utils.h"

SampleTriangle::SampleTriangle() {}

SampleTriangle::~SampleTriangle() {

}

void SampleTriangle::beforeDraw(int screenW, int screenH) {
  if (program != 0) {
    return;
  }

  const char *vShaderCode = GLUtils::loadTextFileFromAsset("shader/triangle_vs.glsl");
  LOGE("vShaderCode : %s", vShaderCode);
  const char *fShaderCode = GLUtils::loadTextFileFromAsset("shader/triangle_fs.glsl");
  LOGE("fShaderCode : %s", fShaderCode);


  program = GLUtils::createProgram(vShaderCode, fShaderCode);
//  program = GLUtils::createProgram(vShaderStr, fShaderStr);

  //2.生成VAO,VBO对象,并绑定顶点属性
  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //顶点坐标属性
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) nullptr);
  glEnableVertexAttribArray(0);

  //颜色
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(GL_NONE);
  glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

}

void SampleTriangle::draw() {
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
  glUseProgram(GL_NONE);
}

void SampleTriangle::destroy() {
  if (program) {
    program = GL_NONE;
  }
  glDeleteVertexArrays(1, &VAO);
}


