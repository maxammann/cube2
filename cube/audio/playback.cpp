#include <ao.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include "playback.h"

bool never_stop() {
    return false;
}

void Playback::play(std::string path, PlaybackScreen &screen, std::function<bool()> stop) const {
    ao_sample_format format;

    memset(&format, 0, sizeof(format));
    format.bits = 16;
    format.channels = 1;
    format.rate = 44100;
    format.byte_format = AO_FMT_LITTLE;

    ao_device *device = ao_open_live(ao_default_driver_id(), &format, nullptr);

    if (device == nullptr) {
        std::cerr << "Error opening device: " << strerror(errno) << std::endl;
    }

    std::ifstream is(path, std::ifstream::binary);
    char buffer[256];

    screen.initVisualize(256 / sizeof(int16_t));

    while (!is.eof()) {
        is.read(buffer, 256);

        if (ao_play(device, buffer, (uint_32) is.gcount()) == 0) {
            std::cerr << "Error during playback: " << strerror(errno) << std::endl;
            break;
        }

        screen.visualize((int16_t *) buffer);

        if (stop()) {
            break;
        }
    }

    is.close();
    ao_close(device);
}

Playback::Playback() {
    ao_initialize();
}

Playback::~Playback() {
    ao_shutdown();
}







