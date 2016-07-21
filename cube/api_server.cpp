#include "api_server.h"
#include <crow.h>
#include <json.hpp>

void APIServer::start() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "/alarm/get - returns alarms\n"
                "/alarm/set - sets alarms";
    });

    CROW_ROUTE(app, "/alarm/get")([this] {
        nlohmann::json j = nlohmann::json::array();

        wakedog.visitAlarms([&j](const Alarm &alarm) {
            nlohmann::json out = nlohmann::json::object();

            out["name"] = alarm.getName();
            out["wake_time"] = alarm.getWakeTime().count();
            out["enabled"] = alarm.isEnabled();

            j.push_back(out);
        });

        return j.dump();
    });

    CROW_ROUTE(app, "/alarm/set").methods("POST"_method) ([this](const crow::request &req) {
        nlohmann::json json;
        std::vector<Alarm> alarms;
        try {
            json = nlohmann::json::parse(req.body);

            for (auto &element : json) {
                alarms.push_back(Alarm(
                        element["name"],
                        std::chrono::duration<int, std::ratio<1, 1>>(element["wake_time"]),
                        element["enabled"])
                );
            }
        } catch (std::invalid_argument e) {
            return crow::response(400);
        }

        std::cout << "Received new alarms" << std::endl;

        wakedog.setAlarms(alarms);

        return crow::response(200);
    });

    app.port(port).multithreaded().run();
}

