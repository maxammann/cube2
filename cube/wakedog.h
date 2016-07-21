#ifndef CUBE2_WAKEDOG_H
#define CUBE2_WAKEDOG_H

#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <algorithm>
#include "alarm.h"
#include "ringer.h"

class Wakedog {
private:
    std::unique_ptr<std::thread> thread;

    bool done = false;

    std::mutex mtx;
    std::condition_variable cv;

    std::vector<Alarm> alarms;

    Ringer &ringer;

    void watch();

public:

    Wakedog(Ringer &ringer) : ringer(ringer) {
        thread = std::unique_ptr<std::thread>(new std::thread([this] {
            watch();
        }));
    }

    ~Wakedog() {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
        cv.notify_one();
        lock.unlock();
        thread->join();
    }

    void setAlarms(const std::vector<Alarm> &new_alarms) {
        std::unique_lock<std::mutex> lock(mtx);
        this->alarms.assign(new_alarms.begin(), new_alarms.end());

        for (Alarm &alarm : alarms) {
            if (alarm.isEager()) {
                alarm.setTriggered(true);
            }
        }

        cv.notify_one();
    }

    template<typename Functor>
    void visitAlarms(Functor f) {
        std::unique_lock<std::mutex> lock(mtx);
        std::for_each(alarms.begin(), alarms.end(), f);
    }
};


#endif //CUBE2_WAKEDOG_H
