#ifndef CUBE2_PLAYBACK_H
#define CUBE2_PLAYBACK_H


#include <functional>
#include "playback_screen.h"

bool never_stop();

class Playback {
public:

    Playback();

    ~Playback();


    void playDefault(char *file_path) const;

    void play(std::string path, PlaybackScreen &screen, std::function<bool()> stop = never_stop) const;
};


#endif //CUBE2_PLAYBACK_H
