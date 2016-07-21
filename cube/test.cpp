#include <Magick++.h>
#include <wiringSerial.h>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
//    Magick::Image image(Magick::Geometry(32, 32), Magick::ColorRGB(0, 0, 0));
//    image.fillColor(Magick::ColorRGB(1, 0, 0));
//    image.draw(Magick::DrawableRectangle(0, 32, 32, 0));
//
//    image.getPixels(0,0,32,32);
//
//    Magick::Geometry geometry = image.size();
//
//    for (int x = 0; x < geometry.width(); ++x) {
//        for (int y = 0; y < geometry.height(); ++y) {
//            Magick::ColorRGB color = image.pixelColor(x, y);
//
//            double red = color.red() * 255.0f;
//            uint8_t i = (uint8_t) red;
//            std::cout << "red: " << red << std::endl;
//        }
//    }

    int fd;

    if ((fd = serialOpen("/dev/ttyUSB0", 115200)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }

    for (int y = 0; y < 32; ++y) {
    for (int x = 0; x < 32; ++x) {
            serialPutchar(fd, 0xff);
            serialPutchar(fd, 0);
            serialPutchar(fd, 0);
        }
        usleep(5000);
    }

    serialFlush(fd);
    serialClose(fd);
    return 0;
}