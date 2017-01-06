#ifndef CUBE2_GIFSCREEN_H
#define CUBE2_GIFSCREEN_H


#include "screen.h"
#include <unistd.h>

class PreprocessedFrame {
private:
    rgb_matrix::FrameCanvas *const canvas_;
    int delay_micros_;
public:
    PreprocessedFrame(const Magick::Image &img,
                      rgb_matrix::FrameCanvas *output);

    rgb_matrix::FrameCanvas *canvas() const { return canvas_; }

    int delay_micros() const {
        return delay_micros_;
    }
};

class GifScreen : public Screen {
private:
    std::vector<PreprocessedFrame *> frames;
    int counter = 0;
public:

    GifScreen(const char *filename, rgb_matrix::RGBMatrix *matrix);

    void draw(rgb_matrix::RGBMatrix &matrix, float elapsed) override;
};


#endif //CUBE2_GIFSCREEN_H
