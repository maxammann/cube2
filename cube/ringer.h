#ifndef CUBE2_RINGER_H
#define CUBE2_RINGER_H


#include "audio/playback.h"
#include "alarm.h"
#include "active_screen.h"

class Ringer {
public:
    virtual void ring(const Alarm &alarm) = 0;
};


class AudioRinger : public Ringer {
private:
    const Playback &playback;
    ScreenTask &screenTask;
    bool stopped;

public:
    AudioRinger(const Playback &playback, ScreenTask &screenTask) : playback(playback), screenTask(screenTask) { }

    ~AudioRinger() {
        stop();
    }

    void ring(const Alarm &alarm);

    void stop() {
        stopped = true;
    }

    bool isStopped() const {
        return stopped;
    }
};


#endif //CUBE2_RINGER_H
