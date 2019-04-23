#include "clock_screen.h"

ClockScreen::ClockScreen(): MagickScreen() {
    canvas.font("DejaVu-Sans-Bold");
    canvas.fontPointsize(13);
    canvas.antiAlias(false);
    canvas.fillColor(Magick::ColorRGB(0, 64, 200));
}

void ClockScreen::draw(Magick::Image &canvas, float elapsed) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto time = localtime(&now);
    char buffer[80];

    strftime(buffer, 80, "%I\n%M", time);

    canvas.textGravity(Magick::GravityType::CenterGravity);

    canvas.draw(Magick::DrawableText(0, 0, std::string(buffer)));
}