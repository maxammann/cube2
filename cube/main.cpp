#include <led-matrix.h>
#include <iostream>
#include <csignal>
#include "canvas.h"
#include "active_screen.h"
#include "api_server.h"
#include "screen/clock_screen.h"
#include "rotary_encoder.h"
#include "screen/mausi_screen.h"
#include "screen/fill_screen.h"
//#include <chrono>

using namespace std;
//using namespace std::chrono;

int main() {
//    auto now = system_clock::to_time_t(system_clock::now());
//    auto time = localtime(&now);
//    std::cout << time->tm_hour << std::endl;

    std::cout << "Initializing audio playback" << std::endl;
    Playback playback;
    AudioRinger ringer(playback);

    std::cout << "Starting wakedog" << std::endl;
    Wakedog wakedog(ringer);

    std::cout << "Starting api server" << std::endl;
    APIServer server(8081, wakedog);

//    server.start();

    std::cout << "Initializing gpio" << std::endl;
    rgb_matrix::GPIO io;
    if (!io.Init()) {
        std::cerr << "Failed to initialize GPIO interface!" << std::endl;
        return 1;
    }

    setupencoder(19, 16, 13, [&ringer](bool down) { if (down) { ringer.stop(); } });

    std::cout << "Starting rendering service" << std::endl;
    rgb_matrix::RGBMatrix device_link(&io, 32, 1, 1);
    //    device_link.set_luminance_correct(false);
//    device_link.SetPWMBits(2);
//    device_link.Fill(100,70,111);
    RealCanvas canvas(&device_link);


//    DumpCanvas canvas;

//
//    canvas.getImage()->fillColor(Magick::ColorRGB(1, 1, 1));
//    canvas.getImage()->draw(Magick::DrawableRectangle(0, 32, 16, 16));
    canvas.getImage()->font("DejaVu-Sans-Mono");
    canvas.getImage()->antiAlias(false);
//    canvas.getImage()->draw(Magick::DrawableText(0, 16, "Clock"));
//    canvas.swap();



    std::cout << "Starting screen service" << std::endl;
    ScreenTask task(&canvas);
//    task.setActiveScreen(new FillScreen());
//    task.setActiveScreen(new ClockScreen());
//    task.setActiveScreen(new MausiScreen());

    server.start();

    std::cerr << "Cube shutting down" << std::endl;
    return 0;
}