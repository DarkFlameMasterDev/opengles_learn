//
// Created by 曹璐韬 on 2023/10/20.
//

#ifndef OPENGLES3_0_SAMPLETRANSFORM_H
#define OPENGLES3_0_SAMPLETRANSFORM_H


#include "SampleBase.h"

class SampleTransform : public SampleBase {

public:
    SampleTransform();

    virtual ~SampleTransform();

    void beforeDraw(int screenW, int screenH) override;

    void draw() override;

    void destroy() override;

private:
    GLuint VAO;
    GLuint VBO;
};


#endif //OPENGLES3_0_SAMPLETRANSFORM_H
