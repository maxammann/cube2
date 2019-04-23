#include <led-matrix.h>
#include "active_screen.h"
#include "api_server.h"
#include "rotary_encoder.h"
#include "screen/boot_screen.h"
#include "screen/clock_screen.h"

int main() {
    std::cout << "Initializing gpio" << std::endl;
    rgb_matrix::GPIO io;
    if (!io.Init()) {
        std::cerr << "Failed to initialize GPIO interface!" << std::endl;
        return 1;
    }

    std::cout << "Starting screen service" << std::endl;
    ScreenTask task(io);
    std::cout << "Setting start screen" << std::endl;
    task.startMatrix();
    task.setActiveScreen(new BootScreen());

    std::cout << "Initializing audio playback" << std::endl;
    Playback playback;
    AudioRinger ringer(playback, task);

    std::cout << "Starting wakedog" << std::endl;
    Wakedog wakedog(ringer);

    wakedog.readAlarms("/root/alarms.json");

    std::cout << "Starting api server" << std::endl;
    APIServer server(8081, wakedog);

    setupencoder(19, 16, 13, [&ringer, &task]() {
        if (task.isMatrixRunning()) {
            task.stopMatrix();
        } else {
            task.startMatrix();
        }

        ringer.stop();
    });

    task.stopMatrix();
    task.setActiveScreen(new ClockScreen());

//
//    PlaybackScreen screen;
//    task.setActiveScreen(&screen);
//
//    playback.play("test.raw", screen, [] () { return false;});
//    task.setActiveScreen(EMPTY_SCREEN);
//
//    std::this_thread::sleep_for(std::chrono::seconds(1));

    server.start();
    // Shutting down...

    std::cerr << "Cube shutting down" << std::endl;
    return 0;
}