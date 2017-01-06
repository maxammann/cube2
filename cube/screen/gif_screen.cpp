#include "screen.h"
#include "gif_screen.h"


static inline unsigned char ScaleQuantumToChar(const Magick::Quantum quantum) {
    return ((unsigned char) (((quantum + 128UL) - ((quantum + 128UL) >> 8)) >> 8));
}


PreprocessedFrame::PreprocessedFrame(const Magick::Image &img,
                                     rgb_matrix::FrameCanvas *output)
        : canvas_(output) {
    int delay_time = img.animationDelay();  // in 1/100s of a second.
    if (delay_time < 1) delay_time = 1;
    delay_micros_ = delay_time * 10000;


    for (size_t y = 0; y < img.rows(); ++y) {
        for (size_t x = 0; x < img.columns(); ++x) {
            const Magick::Color &c = img.pixelColor(x, y);
            if (c.alphaQuantum() < 256) {
                output->SetPixel(x, y,
                                 ScaleQuantumToChar(c.redQuantum()),
                                 ScaleQuantumToChar(c.greenQuantum()),
                                 ScaleQuantumToChar(c.blueQuantum()));
            }
        }
    }
}


static bool LoadAnimation(const char *filename, int width, int height,
                          std::vector<Magick::Image> *image_sequence) {
    std::vector<Magick::Image> frames;
    fprintf(stderr, "Read image...\n");
    Magick::readImages(&frames, filename);
    if (frames.size() == 0) {
        fprintf(stderr, "No image found.");
        return false;
    }

    // Put together the animation from single frames. GIFs can have nasty
    // disposal modes, but they are handled nicely by coalesceImages()
    if (frames.size() > 1) {
        fprintf(stderr, "Assembling animation with %d frames.\n",
                (int) frames.size());
        Magick::coalesceImages(image_sequence, frames.begin(), frames.end());
    } else {
        image_sequence->push_back(frames[0]);   // just a single still image.
    }

    fprintf(stderr, "Scale ... %dx%d -> %dx%d\n",
            (int) (*image_sequence)[0].columns(), (int) (*image_sequence)[0].rows(),
            width, height);
    for (size_t i = 0; i < image_sequence->size(); ++i) {
        (*image_sequence)[i].scale(Magick::Geometry(width, height));
    }
    return true;
}


static void PrepareBuffers(const std::vector<Magick::Image> &images,
                           rgb_matrix::RGBMatrix *matrix,
                           std::vector<PreprocessedFrame *> *frames) {
    for (size_t i = 0; i < images.size(); ++i) {
        rgb_matrix::FrameCanvas *canvas = matrix->CreateFrameCanvas();
        frames->push_back(new PreprocessedFrame(images[i], canvas));
    }
}

GifScreen::GifScreen(const char *filename, rgb_matrix::RGBMatrix *matrix) {
    std::vector<Magick::Image> sequence_pics;
    if (!LoadAnimation(filename, 32, 32, &sequence_pics)) {
        return;
    }

    PrepareBuffers(sequence_pics, matrix, &frames);
}

void GifScreen::draw(rgb_matrix::RGBMatrix &matrix, float elapsed) {
    const PreprocessedFrame *frame = frames[++counter % frames.size()];
    matrix.SwapOnVSync(frame->canvas());

    if (frames.size() == 1) {
        sleep(86400);  // Only one image. Nothing to do.
    } else {
        usleep(frame->delay_micros());
    }
}