#include "ringer.h"

void AudioRinger::ring(const Alarm &alarm) {
    Screen *previous = screenTask.getActiveScreen();
    
    PlaybackScreen screen;
    screenTask.setActiveScreen(&screen);
    screenTask.startMatrix();

    stopped = false;
    playback.play("/root/wakeup.raw", screen, [this] () { return stopped;});
    screen.freeVisualize();
    screenTask.setActiveScreen(previous);
}

