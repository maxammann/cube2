#ifndef CUBE2_CANVAS_H
#define CUBE2_CANVAS_H


#include <Magick++.h>
#include <led-matrix.h>

class Canvas {
private:
    Magick::Image image;

public:

    Canvas() : image(Magick::Geometry(32, 32), Magick::ColorRGB(0, 0, 0)) {
        Magick::InitializeMagick(nullptr);
        image.colorspaceType(Magick::RGBColorspace);
    }

    virtual void swap() = 0;

    Magick::Image *getImage() {
        return &image;
    }
};

class RealCanvas : public Canvas {
private:
    rgb_matrix::RGBMatrix *device_link;

public:

    RealCanvas(rgb_matrix::RGBMatrix *device_link) : device_link(device_link), Canvas() {
    }

    void swap();
};

class DumpCanvas : public Canvas {
public:
    void swap();
};


#endif //CUBE2_CANVAS_H
