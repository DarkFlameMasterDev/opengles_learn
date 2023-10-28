//
// Created by 曹璐韬 on 2023/10/15.
//

#include "SampleSquare.h"
#include "GLUtils.h"

SampleSquare::SampleSquare() {}

SampleSquare::~SampleSquare() {

}

void SampleSquare::beforeDraw(int screenW, int screenH) {
  if (program != 0) {
    return;
  }

  //1.创建着色器程序，此处将着色器程序创建封装到一个工具类中
  const char vShaderStr[] =
      "#version 300 es\n"
      "layout(location = 0) in vec3 aPos;\n"
      "layout(location = 1) in vec3 aColor;\n"
      "out vec3 ourColor;\n"
      "void main(){\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "   ourColor = aColor;\n"
      "}\n";

  const char fShaderStr[] =
      "#version 300 es\n"
      "precision mediump float;\n"
      "out vec4 FragColor;\n"
      "in vec3 ourColor;\n"
      "void main(){\n"
      "   FragColor = vec4(ourColor, 1.0f);\n"
      "}\n";

  program = GLUtils::createProgram(vShaderStr, fShaderStr);

  //2.生成VAO,VBO对象,并绑定顶点属性
  GLfloat vertices[] = {
      0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
  };

  GLuint indices[] = {
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //顶点坐标属性
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) nullptr);
  glEnableVertexAttribArray(0);

  //颜色
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(GL_NONE);
  glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

}

void SampleSquare::draw() {
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
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  //解绑VAO
  glBindVertexArray(GL_NONE);
  //解绑程序着色器对象
  glUseProgram(GL_NONE);
}

void SampleSquare::destroy() {
  if (program) {
    program = GL_NONE;
  }
  glDeleteVertexArrays(1, &VAO);
}
