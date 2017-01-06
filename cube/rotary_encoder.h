#pragma once

#include <functional>
#include <chrono>

class encoder_dev {
public:
    int pin_a;
    int pin_b;
    int switch_pin;
    int value = 0;
    int last_seq = 0;
    std::function<void()> button_listener;
    std::chrono::time_point<std::chrono::steady_clock> last_button;
    std::chrono::time_point<std::chrono::steady_clock> last_rotatated = std::chrono::steady_clock::now();
};

void setupencoder(int pin_a, int pin_b, int switch_pin, std::function<void()> button_listener);

void reset_last_down();

void reset_last_up();
