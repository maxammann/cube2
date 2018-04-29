#include <iostream>
#include <fstream>
#include <chrono>
#include "wakedog.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std::chrono;

int getHourOfDay() {
    auto now = system_clock::to_time_t(system_clock::now());
    auto time = localtime(&now);
    return time->tm_hour;
}

bool isNewDay(int previous_hour, int current_hour) {
    return previous_hour == 23 && current_hour == 0;
}

void Wakedog::watch() {
    int previousHour = getHourOfDay();

    while (!done) {
        std::unique_lock<std::mutex> lock(mtx);

        //todo while!
        if (alarms.empty() ||
            std::all_of(alarms.begin(), alarms.end(), [](Alarm alarm) { return !alarm.isEnabled(); })) {
            cv.wait(lock);
        } else {
            cv.wait_for(lock, seconds(5));
        }

        if (done) {
            return;
        }

        int currentHour = getHourOfDay();

        std::vector<Alarm> ring;

        for (Alarm &alarm : alarms) {
            // Reset triggered state on new day
            if (isNewDay(previousHour, currentHour)) {
                alarm.setTriggered(false);
            }

            if (alarm.isEnabled() && !alarm.isTriggered() && alarm.isEager()) {
                //ring ring!
                alarm.setTriggered(true);
                ring.push_back(alarm);
            }
        }

        previousHour = currentHour;

        lock.unlock();

        for (Alarm &alarm : ring) {
            ringer.ring(alarm);
        }
    }
}

void Wakedog::writeAlarms(std::string path) {
    json alarmsArray = json::array();

    visitAlarms([&alarmsArray](Alarm item) {
        json alarm;

        alarm["name"] = item.getName();
        alarm["wake_time"] = item.getWakeTime().count();
        alarm["enabled"] = item.isEnabled();

        json weekdays = json::array();
        for (int i = 0; i < 7; ++i) {
            weekdays.push_back(item.isEnabledOnWeekday((const Weekday &) i));
        }
        alarm["weekdays"] = weekdays;

        alarmsArray.push_back(alarm);
    });

    std::ofstream output(path, std::ios::out | std::ios_base::binary);
    output << alarmsArray;
    output.close();
}

void Wakedog::readAlarms(std::string path) {
    json alarmsArray;
    std::vector<Alarm> newAlarms;

    std::ifstream input(path, std::ios::in | std::ios_base::binary);
    if (input.is_open()) {
        input >> alarmsArray;


        for (json::iterator it = alarmsArray.begin(); it != alarmsArray.end(); ++it) {
            json alarmJson = *it;

            json &jsonWeekdays = alarmJson["weekdays"];
            std::array<bool, 7> weekdays;

            for (int i = 0; i < 7; ++i) {
                weekdays[i] = jsonWeekdays.at(i);
            }

            Alarm alarm(alarmJson["name"], std::chrono::duration<int, std::ratio<1, 1>>(alarmJson["wake_time"]),
                        alarmJson["enabled"], weekdays);
            newAlarms.push_back(alarm);
        }
    }

    input.close();

    setAlarms(newAlarms);
}



