#ifndef CUBE2_API_SERVER_H
#define CUBE2_API_SERVER_H

#include <thread>
#include "wakedog.h"

class APIServer {
private:
    uint16_t port;

    Wakedog &wakedog;
public:

    APIServer(uint16_t port, Wakedog &wakedog) : port(port), wakedog(wakedog) {
    }

    ~APIServer() {
    }

    void start();
};

#endif //CUBE2_API_SERVER_H
