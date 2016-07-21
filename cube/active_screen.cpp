#include <iostream>
#include "active_screen.h"

Screen *EMPTY_SCREEN = new EmptyScreen();

void ScreenTask::run() {
    using namespace std::chrono;

    std::cout << "Starting screen thread" << std::endl;

    using fseconds = duration<float>;

    duration<int64_t, std::nano> idle_time = seconds(1);

    steady_clock::time_point last_time = steady_clock::now();
    steady_clock::time_point current;

    while (!done) {
        std::unique_lock<std::mutex> lock(mutex);

        current = steady_clock::now();

        while (active_screen->isEmpty()) {
            screen_available.wait(lock);
        }

        canvas->getImage()->fillColor(Magick::ColorRGB(0, 0, 0));
        canvas->getImage()->draw(Magick::DrawableRectangle(0, 32, 32, 0));

        active_screen->draw(canvas, duration_cast<fseconds>(current - last_time).count());

        lock.unlock();

        canvas->swap();

        std::this_thread::sleep_for(idle_time);
    }
}

