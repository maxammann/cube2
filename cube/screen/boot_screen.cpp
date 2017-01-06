#include "boot_screen.h"

void BootScreen::draw(Magick::Image &canvas, float elapsed) {
    canvas.draw(Magick::DrawableText(0, 16, "Booting"));
}

BootScreen::BootScreen() : MagickScreen() {
    canvas.font("Droid-Sans-Bold");
    canvas.antiAlias(false);

    canvas.fillColor(Magick::ColorRGB(1, 0, 0));
}