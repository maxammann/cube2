#include <ao.h>
#include <fstream>
#include <cstring>
#include "playback.h"

bool never_stop() {
    return false;
}

void Playback::play(std::string path, double seconds, double max_vol, std::function<bool()> stop) const {
    enum {
        SKIP, STATIC, DYNAMIC
    } vol_state;

    double vol;

    if (seconds == 0) {
        if (max_vol == 1.0) {
            vol_state = SKIP;
            vol = 0;
        } else {
            vol_state = STATIC;
            vol = max_vol;
        }

    } else {
        vol_state = DYNAMIC;
        vol = max_vol / seconds;
    }

    ao_sample_format format;

    memset(&format, 0, sizeof(format));
    format.bits = 16;
    format.channels = 1;
    format.rate = 44100;
    format.byte_format = AO_FMT_LITTLE;

    ao_device *device = ao_open_live(ao_default_driver_id(), &format, nullptr);

    if (device == nullptr) {
        printf("%s\n", strerror(errno));
        throw ("Error opening device" + errno);
    }

//    struct timespec start_time;
//
//    if (vol_state == DYNAMIC) {
//        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
//    }

//    visualize_init(4096 / sizeof(int16_t));

    std::ifstream is (path, std::ifstream::binary);
    char * buffer = new char [256];

    while (!is.eof()) {
        is.read(buffer, 256);

//        if (vol_state == STATIC) {
//            modify_volume((int16_t *) output, out_linesize, vol);
//        } else if (vol_state == DYNAMIC) {
//            struct timespec current;
//            clock_gettime(CLOCK_MONOTONIC_RAW, &current);
//
//            double elapsed = fabs(start_time.tv_sec * 10E9 + start_time.tv_nsec - current.tv_sec * 10E9 +
//                                  current.tv_nsec) / 10E9;
//
//            double volume = fmin(max_vol, vol * elapsed);
//
//            if (volume == 1.0) {
//                vol_state = SKIP;
//            } else {
//                modify_volume((int16_t *) output, out_linesize, volume);
//            }
//        }


        if (ao_play(device, buffer, (uint_32) is.gcount()) == 0) {
            printf("%s\n", strerror(errno));
            printf("ao_play: failed.\n");
            break;
        }

//      buffer_visualize((int16_t *) output);

        if (stop()) {
            break;
        }
    }

    ao_close(device);
}

Playback::Playback() {
    ao_initialize();
}

Playback::~Playback() {
    ao_shutdown();
}







