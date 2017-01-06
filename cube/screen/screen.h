#ifndef CUBE2_SCREEN_H
#define CUBE2_SCREEN_H


#include <Magick++.h>
#include <led-matrix.h>
#include <chrono>

class Screen {
public:
    virtual void draw(rgb_matrix::RGBMatrix &matrix, float elapsed) = 0;

    virtual std::chrono::duration<int64_t, std::nano> getSleepTime() {
        return std::chrono::nanoseconds(16666666);
    }
};

class MagickScreen : public Screen {
protected:
    Magick::Image canvas;
public:
    MagickScreen();

    void draw(rgb_matrix::RGBMatrix &matrix, float elapsed) override;

    virtual void draw(Magick::Image &canvas, float elapsed) = 0;
};


#endif //CUBE2_SCREEN_H
