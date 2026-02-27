#include "health.hpp"

void register_health_routes(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/health")
    ([]() {
        crow::json::wvalue body;
        body["status"] = "ok";
        return crow::response{200, body};
    });
}
