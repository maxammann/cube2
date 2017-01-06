#ifndef CUBE2_BOOTSCREEN_H
#define CUBE2_BOOTSCREEN_H

#include "screen.h"

class BootScreen : public MagickScreen {

public:
    BootScreen();

    void draw(Magick::Image &canvas, float elapsed) override;
};

#endif //CUBE2_BOOTSCREEN_H
