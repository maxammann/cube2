#ifndef CUBE2_PLAYBACK_H
#define CUBE2_PLAYBACK_H


#include <functional>

bool never_stop();

class Playback {
public:

    Playback();

    ~Playback();


    void playDefault(char *file_path, double seconds) const;

    void play(std::string path, double seconds, double max_vol, std::function<bool()> stop = never_stop) const;
};


#endif //CUBE2_PLAYBACK_H
