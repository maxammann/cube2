#include <iostream>
#include "canvas.h"


static inline unsigned char ScaleQuantumToChar(const Magick::Quantum quantum) {
    return((unsigned char) (((quantum+128UL)-((quantum+128UL) >> 8)) >> 8));
}

void RealCanvas::swap() {
//    std::cout << "Swapping canvas" << std::endl;

    Magick::Image *image = getImage();

    rgb_matrix::FrameCanvas *temp = device_link->CreateFrameCanvas();

    Magick::Geometry geometry = image->size();

    for (int x = 0; x < geometry.width(); ++x) {
        for (int y = 0; y < geometry.height(); ++y) {
            Magick::ColorRGB color = image->pixelColor(x, y);

            uint8_t r = ScaleQuantumToChar(color.redQuantum());
            uint8_t g = ScaleQuantumToChar(color.greenQuantum());
            uint8_t b = ScaleQuantumToChar(color.blueQuantum());

//            if (r != 0) {
//                std::cout << "r:" + std::to_string(r) << std::endl;
//            }
//
//            if (g != 0) {
//                std::cout << "g:" + std::to_string(g) << std::endl;
//            }
//
//            if (b != 0) {
//                std::cout << "b:" + std::to_string(b) << std::endl;
//            }


            temp->SetPixel(x, y, r, g, b);
        }
    }

    device_link->SwapOnVSync(temp);
}


void DumpCanvas::swap() {

    Magick::Image *image = getImage();


    Magick::Geometry geometry = image->size();

    for (int x = 0; x < geometry.width(); ++x) {
        for (int y = 0; y < geometry.height(); ++y) {
            Magick::ColorRGB color = image->pixelColor(x, y);

//            Magick::Quantum r = ScaleQuantumToChar(color.redQuantum());
//            Magick::Quantum g = ScaleQuantumToChar(color.greenQuantum());
//            Magick::Quantum b = ScaleQuantumToChar(color.blueQuantum());
            double r = color.red();
            double g = color.green();
            double b = color.blue();

            if (r != 0) {
                std::cout << "r:" + std::to_string(r) << std::endl;
            }

            if (g != 0) {
                std::cout << "g:" + std::to_string(g) << std::endl;
            }

            if (b != 0) {
                std::cout << "b:" + std::to_string(b) << std::endl;
            }
        }
    }
};
