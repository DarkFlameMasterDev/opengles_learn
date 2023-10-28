//
// Created by 曹璐韬 on 2023/10/8.
//

#include "GLUtils.h"
#include "log_utils.h"
#include <cstdlib>
#include <cstring>
#include <GLES2/gl2ext.h>
#include <fstream>
#include <sstream>
#include <android/asset_manager.h>
#include "globalAssetManager.h"

std::string getShaderTypeName(int ID) {
  switch (ID) {
    case 0x8B30:
      return "fragment_shader";
    case 0x8B31:
      return "vertex_shader";
    default:
      return "shader_type_ERROR";
  }
}

/**
 * 加载 Shader
 * @param shaderType
 * @param sourceCode
 * @return
 */
GLuint GLUtils::loadShader(GLenum shaderType, const char *sourceCode) {
  GLuint shader;
  FUN_BEGIN_TIME("GLUtils::loadShader")
    shader = glCreateShader(shaderType);
    if (shader) {
      glShaderSource(shader, 1, &sourceCode, nullptr);
      glCompileShader(shader);
      if (!checkShader(shaderType, shader)) {
        shader = 0;
      }
    }
  FUN_END_TIME("GLUtils::loadShader")
  return shader;
}


char *GLUtils::loadTextFileFromAsset(const char *filePath) {
  if (globalAssetManager == nullptr) {
    return nullptr;
  }
  AAsset *asset = AAssetManager_open(globalAssetManager, filePath, AASSET_MODE_BUFFER);

  if (asset != nullptr) {
    const void *data = AAsset_getBuffer(asset);
    off_t length = AAsset_getLength(asset);

    // 动态分配足够大的缓冲区
    char *code = new char[length + 1];
    std::memcpy(code, data, length);
    code[length] = '\0'; // 添加终止符

    // 关闭文件
    AAsset_close(asset);

    return code;
  }

  return nullptr;
}

unsigned char *GLUtils::loadBinaryFileFromAsset(const char *binaryFilePath) {
  if (globalAssetManager == nullptr) {
    return nullptr;
  }
  AAsset *asset = AAssetManager_open(globalAssetManager, binaryFilePath, AASSET_MODE_UNKNOWN);

  if (asset == nullptr) {
    LOGE("AAssetManager open failed : 无法打开");
    return nullptr;
  }

  auto *data = (unsigned char *) AAsset_getBuffer(asset);
  off_t len = AAsset_getLength(asset);

  auto *binaryFile = new unsigned char[len];

  std::memcpy(binaryFile, data, len);
  AAsset_close(asset);
  return binaryFile;
}


bool GLUtils::checkShader(GLenum shaderType, GLuint shader) {
  GLint compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  // 编译成功直接返回
  if (compiled) {
    return true;
  }
  // 编译失败，获取并打印 log
  GLint infoLen = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
  if (infoLen) {
    char *buf = (char *) malloc((size_t) infoLen);
    if (buf) {
      glGetShaderInfoLog(shader, infoLen, nullptr, buf);
      LOGE("GLUtils::loadShader Could not compile shader %s:\n%s\n",
           getShaderTypeName(shaderType).c_str(), buf);
      free(buf);
    }
    glDeleteShader(shader);
  }
  return false;
}

GLuint GLUtils::createProgram(const char *pVertexShaderSource, const char *pFragShaderSource,
                              GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
  GLuint program = 0;
  FUN_BEGIN_TIME("GLUtils::createProgram")
    vertexShaderHandle = loadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if (!vertexShaderHandle) return program;
    fragShaderHandle = loadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if (!fragShaderHandle) return program;

    program = glCreateProgram();
    if (program) {
      glAttachShader(program, vertexShaderHandle);
      checkGlError("glAttachShader");
      glAttachShader(program, fragShaderHandle);
      checkGlError("glAttachShader");
      glLinkProgram(program);
      if (!checkProgram(vertexShaderHandle, fragShaderHandle, program)) {
        program = 0;
      }
    }
  FUN_END_TIME("GLUtils::createProgram")
  LOGE("GLUtils::createProgram program = %d", program);
  return program;
}

bool GLUtils::checkProgram(GLuint &vertexShaderHandle, GLuint &fragShaderHandle, GLuint program) {
  GLint linkStatus = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

  glDetachShader(program, vertexShaderHandle);
  glDeleteShader(vertexShaderHandle);
  vertexShaderHandle = 0;
  glDetachShader(program, fragShaderHandle);
  glDeleteShader(fragShaderHandle);
  fragShaderHandle = 0;
  // 连接成功直接返回
  if (linkStatus == GL_TRUE) {
    return true;
  }
  // 连接失败，获取并打印 log
  GLint bufLength = 0;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
  if (bufLength) {
    char *buf = (char *) malloc((size_t) bufLength);
    if (buf) {
      glGetProgramInfoLog(program, bufLength, nullptr, buf);
      LOGE("GLUtils::createProgram Could not link program:\n%s\n", buf);
      free(buf);
    }
  }
  glDeleteProgram(program);
  return false;
}

GLuint
GLUtils::createProgramWithFeedback(const char *pVertexShaderSource, const char *pFragShaderSource,
                                   GLuint &vertexShaderHandle, GLuint &fragShaderHandle,
                                   GLchar const **varying, int varyingCount) {
  GLuint program = 0;
  FUN_BEGIN_TIME("GLUtils::createProgramWithFeedback")
    vertexShaderHandle = loadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if (!vertexShaderHandle) return program;

    fragShaderHandle = loadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if (!fragShaderHandle) return program;

    program = glCreateProgram();
    if (program) {
      glAttachShader(program, vertexShaderHandle);
      checkGlError("glAttachShader");
      glAttachShader(program, fragShaderHandle);
      checkGlError("glAttachShader");

      //transform feedback
      glTransformFeedbackVaryings(program, varyingCount, varying, GL_INTERLEAVED_ATTRIBS);
      GO_CHECK_GL_ERROR();

      glLinkProgram(program);
      GLint linkStatus = GL_FALSE;
      glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

      glDetachShader(program, vertexShaderHandle);
      glDeleteShader(vertexShaderHandle);
      vertexShaderHandle = 0;
      glDetachShader(program, fragShaderHandle);
      glDeleteShader(fragShaderHandle);
      fragShaderHandle = 0;
      if (linkStatus != GL_TRUE) {
        GLint bufLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
        if (bufLength) {
          char *buf = (char *) malloc((size_t) bufLength);
          if (buf) {
            glGetProgramInfoLog(program, bufLength, nullptr, buf);
            LOGE("GLUtils::createProgramWithFeedback Could not link program:\n%s\n", buf);
            free(buf);
          }
        }
        glDeleteProgram(program);
        program = 0;
      }
    }
  FUN_END_TIME("GLUtils::createProgramWithFeedback")
  LOGE("GLUtils::createProgramWithFeedback program = %d", program);
  return program;
}

void GLUtils::deleteProgram(GLuint &program) {
  LOGE("GLUtils::deleteProgram");
  if (program) {
    glUseProgram(0);
    glDeleteProgram(program);
    program = 0;
  }
}

void GLUtils::checkGlError(const char *pGLOperation) {
  for (GLint error = glGetError(); error; error = glGetError()) {
    LOGE("GLUtils::checkGlError GL Operation %s() glError (0x%x)\n", pGLOperation, error);
  }

}

GLuint GLUtils::createProgram(const char *pVertexShaderSource, const char *pFragShaderSource) {
  GLuint vertexShaderHandle, fragShaderHandle;
  return createProgram(pVertexShaderSource, pFragShaderSource, vertexShaderHandle,
                       fragShaderHandle);
}


