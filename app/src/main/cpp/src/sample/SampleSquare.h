//
// Created by 曹璐韬 on 2023/10/15.
//

#ifndef OPENGLES3_0_SAMPLESQUARE_H
#define OPENGLES3_0_SAMPLESQUARE_H

#include "SampleBase.h"

class SampleSquare : public SampleBase {

public:
    SampleSquare();

    virtual ~SampleSquare();

    void beforeDraw(int screenW, int screenH) override;

    void draw() override;

    void destroy() override;

private:
    GLuint VAO;
    GLuint VBO;
};


#endif //OPENGLES3_0_SAMPLESQUARE_H
