#ifndef CUBE2_CLOCKSCREEN_H
#define CUBE2_CLOCKSCREEN_H


#include "screen.h"

class ClockScreen: public Screen {

public:
    void draw(Canvas *canvas, float elapsed) override {
        canvas->getImage()->fillColor(Magick::ColorRGB(1, 0, 0));
//        canvas->getImage()->draw(Magick::DrawableRectangle(0, 32, 32, 0));
        canvas->getImage()->draw(Magick::DrawableText(0, 16, "Clock"));
    }

    bool isEmpty() override {
        return false;
    }
};


#endif //CUBE2_CLOCKSCREEN_H
