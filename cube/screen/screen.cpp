#include "screen.h"

static inline unsigned char ScaleQuantumToChar(const Magick::Quantum quantum) {
    return ((unsigned char) (((quantum + 128UL) - ((quantum + 128UL) >> 8)) >> 8));
}

void MagickScreen::draw(rgb_matrix::RGBMatrix &matrix, float elapsed) {
    Magick::Color previous = canvas.fillColor();
    canvas.fillColor(Magick::ColorRGB(0, 0, 0));
    canvas.draw(Magick::DrawableRectangle(0, 0, 31, 31));
    canvas.fillColor(previous);
    draw(canvas, elapsed);

//    rgb_matrix::FrameCanvas *temp = matrix.CreateFrameCanvas();

    Magick::Geometry geometry = canvas.size();

    for (int x = 0; x < geometry.width(); ++x) {
        for (int y = 0; y < geometry.height(); ++y) {
            Magick::ColorRGB color = canvas.pixelColor(x, y);

            uint8_t r = ScaleQuantumToChar(color.redQuantum());
            uint8_t g = ScaleQuantumToChar(color.greenQuantum());
            uint8_t b = ScaleQuantumToChar(color.blueQuantum());


//            temp->SetPixel(x, y, r, g, b);
            matrix.SetPixel(x, y, r, g, b);
        }
    }

//    matrix.SwapOnVSync(temp);
}

MagickScreen::MagickScreen() : canvas(Magick::Geometry(32, 32), Magick::ColorRGB(0, 0, 0)) {
    canvas.colorspaceType(Magick::RGBColorspace);
}
