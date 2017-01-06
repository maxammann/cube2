#ifndef CUBE2_ACTIVESCREEN_H
#define CUBE2_ACTIVESCREEN_H


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "screen/screen.h"
#include "canvas.h"

extern Screen *EMPTY_SCREEN;

class ScreenTask {
private:

    std::thread thread;
    Screen *active_screen = EMPTY_SCREEN;
    bool done = false;

    std::mutex matrix_mutex;
    std::condition_variable screen_available;

    rgb_matrix::RGBMatrix *matrix = nullptr;
    rgb_matrix::GPIO io;

    void run();

public:

    ScreenTask(rgb_matrix::GPIO &io) : io(io), matrix_mutex(), screen_available() {
        thread = std::thread([this] { this->run(); });
    }

    void startMatrix();

    bool isMatrixRunning();

    void stopMatrix();

    ~ScreenTask() {
        done = true;
        stopMatrix();
        thread.join();
    }

    void setActiveScreen(Screen *screen);

    Screen *getActiveScreen() const;
};


#endif //CUBE2_ACTIVESCREEN_H
