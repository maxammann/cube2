#ifndef CUBE2_MAUSISCREEN_H
#define CUBE2_MAUSISCREEN_H


#include "screen.h"

class MausiScreen: public Screen {

public:
    void draw(Canvas *canvas, float elapsed) override {
        canvas->getImage()->fillColor(Magick::ColorRGB(1, 1, 1));
//        canvas->getImage()->fillColor(Magick::ColorRGB(0, 0, 0));
//        canvas->getImage()->fillColor(Magick::ColorRGB(255, 255, 255));
        canvas->getImage()->fontPointsize(10);
//        canvas->getImage()->draw(Magick::DrawableRectangle(0, 32, 32, 0));
        canvas->getImage()->draw(Magick::DrawableText(0, 16, "Mausi\n♥"));
    }

    bool isEmpty() override {
        return false;
    }
};


#endif //CUBE2_MAUSISCREEN_H
