#include <wiringPi.h>
#include "rotary_encoder.h"
#include "screen/screen.h"

static std::chrono::time_point<std::chrono::steady_clock> last_down;
static std::chrono::time_point<std::chrono::steady_clock> last_up;

static encoder_dev encoder;

static void button() {
    int down;

    down = !digitalRead(encoder.switch_pin);

    auto now = std::chrono::steady_clock::now();

    if (down) {
        last_down = now;

//        if (get_current_screen() == NULL) {
//            set_current_screen(get_screen("menu"), NULL);
//            lm_thread_unpause(get_thread());
//        }
//
//        skip_current_playback();
//#ifdef DEBUG
        printf("Button down\n");
        encoder.button_listener(true);
//#endif
    } else {
        last_up = now;

//        if (get_current_menu() == 2) {
//            next_alarm();
//        }

//#ifdef DEBUG
        printf("Button up\n");
        encoder.button_listener(false);
//#endif
    }
}

int last_down_longer_than(std::chrono::time_point<std::chrono::steady_clock> time) {
    auto now = std::chrono::steady_clock::now();
    auto duration_since_time = now - time;
    return last_down < now - duration_since_time;
}

int last_up_longer_than(std::chrono::time_point<std::chrono::steady_clock> time) {
    auto now = std::chrono::steady_clock::now();
    auto duration_since_time = now - time;
    return last_up < now - duration_since_time;
}

//int last_rotated_longer_than(std::chrono::time_point<std::chrono::steady_clock> time) {
//    auto now = std::chrono::steady_clock::now();
//    return encoder.last_rotatated < now - time;
//}

//void reset_last_down() {
//    last_down = 0;
//}
//
//void reset_last_up() {
//    last_up = 0;
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

    printf("Value: %d\n", encoder.value);
}

void setupencoder(int pin_a, int pin_b, int switch_pin, std::function<void(bool)> button_listener) {
    wiringPiSetupGpio();

    encoder.pin_a = pin_a;
    encoder.pin_b = pin_b;
    encoder.switch_pin = switch_pin;
    encoder.button_listener = button_listener;

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
