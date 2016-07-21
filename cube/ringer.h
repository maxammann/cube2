#ifndef CUBE2_RINGER_H
#define CUBE2_RINGER_H


#include "audio/playback.h"
#include "alarm.h"

class Ringer {
public:
    virtual void ring(const Alarm &alarm) = 0;
};


class AudioRinger : public Ringer {
private:
    const Playback &playback;
    bool stopped;

public:
    AudioRinger(const Playback &playback) : playback(playback) { }

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
