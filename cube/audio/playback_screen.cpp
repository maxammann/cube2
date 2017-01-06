#include <thread>
#include "playback_screen.h"


constexpr double pi() { return std::atan(1) * 4; }

void PlaybackScreen::initVisualize(int samples) {
    for (int i = 0; i < BANDS; ++i) {
        bands[i] = 0;
    }

    N = samples;
    input = (double *) fftw_malloc(sizeof(double) * N);
    output = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N);

    plan = fftw_plan_dft_r2c_1d(N, input, output, FFTW_ESTIMATE);
}

void PlaybackScreen::freeVisualize() {
    fftw_free(input);
    fftw_free(output);
    fftw_destroy_plan(plan);
}

void PlaybackScreen::draw(rgb_matrix::RGBMatrix &matrix, float elapsed) {
    matrix.Clear();
//    rgb_matrix::FrameCanvas *canvas = matrix.CreateFrameCanvas();

    int16_t band, segment_height, segment_x;

    for (band = 0; band < BANDS; ++band) {
        for (segment_x = 0; segment_x < (32 / BANDS); ++segment_x) {
            for (segment_height = 0; segment_height < bands[band]; ++segment_height) {

                int x = band * (32 / BANDS) + segment_x;
                int y = HEIGHT - segment_height;

                if (x > 31 || segment_height > 31) {
                    continue;
                }

                matrix.SetPixel(x, y, 170, 98, 35);
            }
        }
    }
//    matrix.SwapOnVSync(canvas);
}

void PlaybackScreen::visualize(int16_t *raw) {
    int i; // just some iterator indices

    for (i = 0; i < N; ++i) {
        int16_t data = raw[i];

        long double window_modifier = (0.5 * (1 - cos(2 * 3.1415 * i / (N - 1)))); // Hann (Hanning) window function
        double value = (double) (window_modifier * ((data) / 32768.0f)); // Convert to float and apply

        // cap values above 1 and below -1
        if (value > 1.0) {
            value = 1;
        } else if (value < -1.0) {
            value = -1;
        }

        input[i] = value;
    }

    fftw_execute_dft_r2c(plan, input, output);

    int size = N / 2; // half is usable, but we have re and im

    int band_index;
    for (i = 0, band_index = 0; i < size; i += size / BANDS) {
        int part = size / BANDS;
        double average_value = 0;

        for (int j = 0; j < part; ++j) {
            double re = output[i + j][0];
            double im = output[i + j][1];

            average_value += im * im + re * re;
        }

        average_value /= (float) part;


        long double mag;
        if (average_value == 0) {
            mag = 0;
        } else {
            mag = abs(10 * log10(average_value)) / 80.0;  // The magnitude in logarithmic scale,
            // linear would be sqrt(im * im + re * re)
        }

        if (mag > 1.0) {
            mag = 1;
        }

        if (band_index >= BANDS) {
            break;
        }

        // Visualize magnitude of i-th band
        bands[band_index] = (int16_t) (mag * HEIGHT);
        band_index++;
    }
}
