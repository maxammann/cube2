#include <wiringPi.h>
#include "rotary_encoder.h"
#include "screen/screen.h"



static encoder_dev encoder;

static void button() {
    auto now = std::chrono::steady_clock::now();

    if (encoder.last_button + std::chrono::milliseconds(500) < now) {
        encoder.button_listener();
        encoder.last_button = now;
    }
}

//int last_down_longer_than(std::chrono::time_point<std::chrono::steady_clock> time) {
//    auto now = std::chrono::steady_clock::now();
//    auto duration_since_time = now - time;
//    return last_button < now - duration_since_time;
//}
//
//int last_up_longer_than(std::chrono::time_point<std::chrono::steady_clock> time) {
//    auto now = std::chrono::steady_clock::now();
//    auto duration_since_time = now - time;
//    return last_up < now - duration_since_time;
//}

void updateEncoder() {

    int MSB = digitalRead(encoder.pin_a);
    int LSB = digitalRead(encoder.pin_b);

    int encoded = (MSB << 1) | LSB;
    int sum = (encoder.last_seq << 2) | encoded;

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        encoder.value++;
    }
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        encoder.value--;
    }

    encoder.last_seq = encoded;
    encoder.last_rotatated = std::chrono::steady_clock::now();

//    printf("Value: %d\n", encoder.value);
}

void setupencoder(int pin_a, int pin_b, int switch_pin, std::function<void()> button_listener) {
    wiringPiSetupGpio();

    encoder.pin_a = pin_a;
    encoder.pin_b = pin_b;
    encoder.switch_pin = switch_pin;
    encoder.button_listener = button_listener;
    encoder.last_button = std::chrono::steady_clock::now();

    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
    pullUpDnControl(pin_a, PUD_UP);
    pullUpDnControl(pin_b, PUD_UP);

    pinMode(switch_pin, INPUT);
    pullUpDnControl(switch_pin, PUD_UP);

    wiringPiISR(pin_a, INT_EDGE_BOTH, updateEncoder);
    wiringPiISR(pin_b, INT_EDGE_BOTH, updateEncoder);

    wiringPiISR(switch_pin, INT_EDGE_BOTH, button);
}
