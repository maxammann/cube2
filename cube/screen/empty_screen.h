#ifndef CUBE2_EMPTYSCREEN_H
#define CUBE2_EMPTYSCREEN_H


#include "screen.h"

class EmptyScreen: public Screen {

public:
    void draw(Canvas *canvas, float elapsed) override {

    }

    bool isEmpty() override {
        return true;
    }
};


#endif //CUBE2_EMPTYSCREEN_H
