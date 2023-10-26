//
// Created by 曹璐韬 on 2023/10/25.
//

#include "SampleTexture.h"
#include "log_utils.h"
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

}

void SampleTexture::draw() {

}

void SampleTexture::destroy() {

}
