#ifndef CUBE2_EMPTYSCREEN_H
#define CUBE2_EMPTYSCREEN_H


#include "screen.h"

class EmptyScreen: public Screen {

public:
    void draw(rgb_matrix::RGBMatrix &matrix, float elapsed) override {
    }
};


#endif //CUBE2_EMPTYSCREEN_H
