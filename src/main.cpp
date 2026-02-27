#include "crow.h"
#include "routes/health.hpp"
#include "routes/items.hpp"

int main()
{
    crow::SimpleApp app;

    // Register routes
    register_health_routes(app);
    register_items_routes(app);

    const uint16_t port = 30009;
    app.port(port).multithreaded().run();

    return 0;
}
