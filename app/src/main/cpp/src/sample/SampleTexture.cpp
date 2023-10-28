//
// Created by 曹璐韬 on 2023/10/25.
//

#include "SampleTexture.h"
#include "log_utils.h"
#include "GLUtils.h"

#define  STB_IMAGE_STATIC
#define  STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

SampleTexture::SampleTexture() {

}

SampleTexture::~SampleTexture() {

}

void SampleTexture::beforeDraw(int screenW, int screenH) {
  if (program != 0) {
    return;
  }

  char *vertexShader = GLUtils::loadTextFileFromAsset("shader/texture_vs.glsl");
  char *fragmentShader = GLUtils::loadTextFileFromAsset("shader/texture_fs.glsl");

  program = GLUtils::createProgram(vertexShader, fragmentShader);

  float vertices[] = {
      // positions
      // colors
      // texture coords
      0.5f, 0.5f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, // top right

      0.5f, -0.5f, 0.0f,
      0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, // bottom right

      -0.5f, -0.5f, 0.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, // bottom left

      -0.5f, 0.5f, 0.0f,
      1.0f, 1.0f, 0.0f,
      0.0f, 1.0f  // top left
  };

  GLuint indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture coords attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(GL_NONE);
  glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  float border[4] = {1.0f, 1.0f, 0.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;

  stbi_set_flip_vertically_on_load(true);

  unsigned char *byteArray = GLUtils::loadBinaryFileFromAsset("texture/awesomeface.png");
  const auto *buffer = reinterpret_cast<const stbi_uc *>(byteArray);

  auto length = strlen((const char *) byteArray);
  int len;
  if (length > std::numeric_limits<long>::max()) {
    len = (int) length;
  } else {
    len = 0;
  }
  unsigned char *data = stbi_load_from_memory(buffer, len, &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    LOGE("Failed to load texture");
  }
  stbi_image_free(data);
}

void SampleTexture::draw() {
  if (program == 0) {
    return;
  }
  //清除buffer
  glClearColor(0.3f, 0.5f, 0.4f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindTexture(GL_TEXTURE_2D, texture);

  glUseProgram(program);
  glBindVertexArray(VAO);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  //解绑VAO
  glBindVertexArray(GL_NONE);
  //解绑程序着色器对象
  glUseProgram(GL_NONE);
}

void SampleTexture::destroy() {
  if (program) {
    program = GL_NONE;
  }
  glDeleteVertexArrays(1, &VAO);
}
