#ifndef CUBE2_PLAYBACKSCREEN_H
#define CUBE2_PLAYBACKSCREEN_H


#include "../screen/screen.h"
#include <fftw3.h>

#define HEIGHT 32
#define BANDS 8

class PlaybackScreen: public Screen {
private:
    float bands[BANDS]; // frequency bands

    int N;
    fftw_plan plan;
    double *input;
    fftw_complex *output;
public:

    void draw(rgb_matrix::RGBMatrix &matrix, float elapsed) override;

    void visualize(int16_t *raw);

    void initVisualize(int samples);

    void freeVisualize();
};




#endif //CUBE2_PLAYBACKSCREEN_H
