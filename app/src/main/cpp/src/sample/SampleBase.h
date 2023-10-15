//
// Created by 曹璐韬 on 2023/10/10.
//

#ifndef OPENGLES3_0_SAMPLEBASE_H
#define OPENGLES3_0_SAMPLEBASE_H

#include "stdint.h"
#include <GLES3/gl3.h>

class SampleBase {
public:
    SampleBase() {
      program = 0;

      surfaceWidth = 0;
      surfaceHeight = 0;

    }

    virtual ~SampleBase() {

    }

    virtual void beforeDraw(int screenW, int screenH) = 0;
    virtual void draw() = 0;

    virtual void destroy() = 0;

protected:
    GLuint program;
    int surfaceWidth;
    int surfaceHeight;
};

#endif //OPENGLES3_0_SAMPLEBASE_H
