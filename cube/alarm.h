#ifndef CUBE2_ALARM_H
#define CUBE2_ALARM_H

#include <string>
#include <chrono>

class Alarm {
    std::string name;
    std::chrono::duration<int, std::ratio<1, 1>> wake_time;
    bool enabled;

    bool triggered;

public:

    Alarm(const std::string &name, const std::chrono::duration<int, std::ratio<1, 1>> &wake_time, bool enabled) : name(
            name), wake_time(wake_time), enabled(enabled) { }

    const std::string &getName() const {
        return name;
    }

    bool isEnabled() const {
        return enabled;
    }

    const std::chrono::duration<int, std::ratio<1, 1>> &getWakeTime() const {
        return wake_time;
    }

    bool isEager() const;


    bool isTriggered() const {
        return triggered;
    }


    void setTriggered(bool triggered) {
        Alarm::triggered = triggered;
    }
};

bool compare_alarm(Alarm lhs, Alarm rhs);

#endif //CUBE2_ALARM_H
