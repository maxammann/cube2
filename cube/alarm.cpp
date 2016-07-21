#include "alarm.h"

using namespace std::chrono;

bool Alarm::isEager() const {
    auto now = system_clock::to_time_t(system_clock::now());
    auto time = localtime(&now);

    auto duration_of_day(hours(time->tm_hour) + minutes(time->tm_min) + seconds(time->tm_sec));

    return duration_of_day >= this->wake_time;
}

bool compare_alarm(Alarm lhs, Alarm rhs) { return lhs.getWakeTime() < rhs.getWakeTime(); }
