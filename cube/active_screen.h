#ifndef CUBE2_ACTIVESCREEN_H
#define CUBE2_ACTIVESCREEN_H



#include <thread>
#include <mutex>
#include <condition_variable>

#include "screen/screen.h"
#include "screen/empty_screen.h"
#include "canvas.h"

extern Screen *EMPTY_SCREEN;

class ScreenTask {
private:

    std::unique_ptr<std::thread> thread;
    Screen *active_screen = EMPTY_SCREEN;
    bool done = false;

    std::mutex mutex;
    std::condition_variable screen_available;

    Canvas *canvas;

    void run();

public:

    ScreenTask(Canvas *canvas) : done(false), canvas(canvas) {
        thread = std::unique_ptr<std::thread>(new std::thread([this] { this->run(); }));
    }

    ~ScreenTask() {
        done = true;
        thread->join();
    }

    void setActiveScreen(Screen *screen) {
        std::unique_lock<std::mutex> lock(mutex);
        active_screen = screen;
        screen_available.notify_one();
    }
};


#endif //CUBE2_ACTIVESCREEN_H
