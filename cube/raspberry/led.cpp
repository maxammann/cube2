#include "led.h"
#include <stdio.h>
#include <usb.h>
#include <string>
#include <fcntl.h>

#define NET_VENDOR_ID        0x0424
#define    NET_PRODUCT_ID        0xec00

#define MODE_OFF        0
#define MODE_ON            1

void write_config(usb_dev_handle *devh, unsigned int value) {
    int ret;
    ret = usb_control_msg(devh, 0x40, 0xA0, 0, 0x24, (char *) &value, 4, 5000);
}

struct usb_device *get_usb_device(struct usb_bus *bus, struct usb_device *usbdev) {
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_busses; bus; bus = bus->next) {
        for (usbdev = bus->devices; usbdev; usbdev = usbdev->next) {
            if ((usbdev->descriptor.idVendor == NET_VENDOR_ID) &&
                (usbdev->descriptor.idProduct == NET_PRODUCT_ID)) {
                return (usbdev);
            }
        }
    }

}

static void setLEDState(int led, int state) {
    int fd;

    fd = open(("/sys/class/leds/led" + std::to_string(led) + "/brightness").c_str(), O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open led for writing!\n");
        return;
    }


    std::string buf = std::to_string(state);
    write(fd, buf.c_str(), buf.length());
    close(fd);
}

void turnNetworkOff() {

    struct usb_bus *bus;
    struct usb_device *usbdev;
    struct usb_device *lan9512;
    usb_dev_handle *devh;

    lan9512 = get_usb_device(bus, usbdev);

    if (lan9512 == nullptr) {
        return;
    }

    devh = usb_open(lan9512);


    write_config(devh, MODE_OFF);
    usb_close(devh);
}

void off() {
    turnNetworkOff();
    setLEDState(0, 0);
    setLEDState(1, 0);
}

void on() {
}