//
// Created by 曹璐韬 on 2023/10/8.
//

#ifndef OPENGLES3_0_SAMPLETRIANGLE_H
#define OPENGLES3_0_SAMPLETRIANGLE_H

#include "SampleBase.h"

class SampleTriangle : public SampleBase {

public:
    SampleTriangle();

    virtual ~SampleTriangle();

    void beforeDraw(int screenW, int screenH) override;

    void draw() override;

    void destroy() override;

private:
    GLuint VAO;
    GLuint VBO;
};


#endif //OPENGLES3_0_SAMPLETRIANGLE_H
