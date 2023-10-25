//
// Created by 曹璐韬 on 2023/10/25.
//

#ifndef OPENGLES3_0_SAMPLETEXTURE_H
#define OPENGLES3_0_SAMPLETEXTURE_H


#include "SampleBase.h"

class SampleTexture  : public SampleBase {
public:
    SampleTexture();

    virtual ~SampleTexture();

    void beforeDraw(int screenW, int screenH) override;

    void draw() override;

    void destroy() override;

private:
    GLuint VAO;
    GLuint VBO;
};


#endif //OPENGLES3_0_SAMPLETEXTURE_H
