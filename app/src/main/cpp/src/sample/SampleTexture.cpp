//
// Created by 曹璐韬 on 2023/10/25.
//

#include "SampleTexture.h"
#include "log_utils.h"
#include "filesystem.h"
#include <cstdlib>

#define  STB_IMAGE_STATIC
#define  STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

SampleTexture::SampleTexture() {

}

SampleTexture::~SampleTexture() {

}

void SampleTexture::beforeDraw(int screenW, int screenH) {

  float vertices[] = {
      // positions // colors // texture coords
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

  std::string vertexPath = FileSystem::getPath("src/3_Textures/texture_vs.glsl");
  LOGE("vertexPath: %s", vertexPath.c_str());
  std::string fragmentPath = FileSystem::getPath("src/3_Textures/texture_fs.glsl");
  LOGE("fragmentPath: %s", fragmentPath.c_str());


}

void SampleTexture::draw() {

}

void SampleTexture::destroy() {

}
