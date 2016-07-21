#ifndef CUBE2_FILLSCREEN_H
#define CUBE2_FILLSCREEN_H


#include "screen.h"

class FillScreen: public Screen {

public:
    void draw(Canvas *canvas, float elapsed) override {
        canvas->getImage()->fillColor(Magick::ColorRGB(1, 1, 1));
        canvas->getImage()->draw(Magick::DrawableRectangle(0, 32, 32, 0));
    }

    bool isEmpty() override {
        return false;
    }
};


#endif //CUBE2_FILLSCREEN_H
