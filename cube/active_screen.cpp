#include <iostream>
#include "active_screen.h"
#include "screen/empty_screen.h"

Screen *EMPTY_SCREEN = new EmptyScreen();

void ScreenTask::run() {
    using namespace std::chrono;

    std::cout << "Starting screen thread" << std::endl;

    using fseconds = duration<float>;

    steady_clock::time_point last_time = steady_clock::now();
    steady_clock::time_point current;

    while (!done) {
        std::unique_lock<std::mutex> lock(matrix_mutex);
        
        current = steady_clock::now();

        while (matrix == nullptr) {
            screen_available.wait(lock);

            if (done) {
                return;
            }
        }
        
        active_screen->draw(*matrix, duration_cast<fseconds>(current - last_time).count());
        auto sleepTime = active_screen->getSleepTime();
        lock.unlock();

        std::this_thread::sleep_for(sleepTime);
    }
}

void ScreenTask::setActiveScreen(Screen *screen) {
    std::unique_lock<std::mutex> lock(matrix_mutex);
    active_screen = screen;
}

Screen *ScreenTask::getActiveScreen() const {
    return active_screen;
}

void ScreenTask::startMatrix() {
    std::unique_lock<std::mutex> lock(matrix_mutex);
    if (matrix == nullptr) {
        std::cout << "Starting rendering service" << std::endl;
        matrix = new rgb_matrix::RGBMatrix(&io, 32, 1, 1);
        matrix->set_luminance_correct(true);
        matrix->SetPWMBits(4);
    }
    lock.unlock();
    screen_available.notify_one();
}

bool ScreenTask::isMatrixRunning() {
    std::unique_lock<std::mutex> lock(matrix_mutex);
    return matrix != nullptr;
}

void ScreenTask::stopMatrix() {
    std::unique_lock<std::mutex> lock(matrix_mutex);
    std::cout << "Stopping rendering service" << std::endl;
    if (matrix != nullptr) {
        delete matrix;
        matrix = nullptr;
    }
    lock.unlock();
    screen_available.notify_one();
}

