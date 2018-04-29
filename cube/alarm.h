#ifndef CUBE2_ALARM_H
#define CUBE2_ALARM_H

static const int DAYS_IN_WEEK = 7;

#include <string>
#include <chrono>
#include <array>
#include <iostream>
#include <boost/range/size_type.hpp>


//enum Weekday {
//    MONDAY = 0,
//    TUESDAY = 1,
//    WEDNESDAY = 2,
//    THURSDAY = 3,
//    FRIDAY = 4,
//    SATURDAY = 5,
//    SUNDAY = 6
//};

class Alarm {
private:
    std::string name;
    std::chrono::duration<int, std::ratio<1, 1>> wake_time;
    bool enabled;

    bool triggered;

    std::array<bool, 7> weekdays;

public:

    Alarm(const std::string &name, const std::chrono::duration<int, std::ratio<1, 1>> &wake_time, bool enabled,
          std::array<bool, 7> &weekdays) : name(name), wake_time(wake_time), enabled(enabled), weekdays(weekdays) {
    }

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

    bool isEnabledOnWeekday(int weekday) const {
        return weekdays.at(weekday);
    }

    void setTriggered(bool triggered) {
        Alarm::triggered = triggered;
    }

    const std::array<bool, 7> getWeekdays() const {
        return weekdays;
    }
};

bool compare_alarm(Alarm lhs, Alarm rhs);

#endif //CUBE2_ALARM_H
