#include <iostream>
#include "wakedog.h"

void Wakedog::watch() {
    while (!done) {
        std::unique_lock<std::mutex> lock(mtx);

        if (alarms.empty() || std::all_of(alarms.begin(), alarms.end(), [] (Alarm alarm) {return !alarm.isEnabled();})) {
            cv.wait(lock);
        } else {
            cv.wait_for(lock, std::chrono::seconds(5));
        }

        std::vector<Alarm> ring;

        for (Alarm &alarm : alarms) {
            if (alarm.isEnabled() && !alarm.isTriggered() && alarm.isEager()) {
                //ring ring!
                alarm.setTriggered(true);
                ring.push_back(alarm);
            }
        }

        lock.unlock();

        for (Alarm &alarm : ring) {
            ringer.ring(alarm);
        }
    }
}



