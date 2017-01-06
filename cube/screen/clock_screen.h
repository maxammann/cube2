#ifndef CUBE2_CLOCKSCREEN_H
#define CUBE2_CLOCKSCREEN_H


#include "screen.h"

class ClockScreen : public MagickScreen {

public:
    ClockScreen();

    void draw(Magick::Image &canvas, float elapsed) override;
};


#endif //CUBE2_CLOCKSCREEN_H
