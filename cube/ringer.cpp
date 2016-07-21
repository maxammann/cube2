#include "ringer.h"

void AudioRinger::ring(const Alarm &alarm) {
    stopped = false;
    playback.play("test.raw", 0, 0, [this] () { return stopped;});
}

