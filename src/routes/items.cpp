#include "items.hpp"
#include <mutex>
#include <unordered_map>
#include <atomic>

// In-memory store — replace with a real database layer
static std::unordered_map<int, std::string> items_store;
static std::atomic<int> next_id{1};
static std::mutex store_mutex;

void register_items_routes(crow::SimpleApp& app)
{
    // GET /items — list all items
    CROW_ROUTE(app, "/items")
    ([]() {
        std::lock_guard<std::mutex> lock(store_mutex);
        crow::json::wvalue result;
        crow::json::wvalue::list arr;
        for (const auto& [id, name] : items_store) {
            crow::json::wvalue entry;
            entry["id"]   = id;
            entry["name"] = name;
            arr.push_back(std::move(entry));
        }
        result["items"] = std::move(arr);
        return crow::response{200, result};
    });

    // GET /items/<id> — get one item
    CROW_ROUTE(app, "/items/<int>")
    ([](int id) {
        std::lock_guard<std::mutex> lock(store_mutex);
        auto it = items_store.find(id);
        if (it == items_store.end()) {
            return crow::response{404, R"({"error":"not found"})"};
        }
        crow::json::wvalue body;
        body["id"]   = id;
        body["name"] = it->second;
        return crow::response{200, body};
    });

    // POST /items — create an item
    CROW_ROUTE(app, "/items").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("name")) {
            return crow::response{400, R"({"error":"'name' field required"})"};
        }
        std::lock_guard<std::mutex> lock(store_mutex);
        int id = next_id++;
        items_store[id] = body["name"].s();
        crow::json::wvalue resp;
        resp["id"]   = id;
        resp["name"] = items_store[id];
        return crow::response{201, resp};
    });

    // DELETE /items/<id> — remove an item
    CROW_ROUTE(app, "/items/<int>").methods(crow::HTTPMethod::DELETE)
    ([](int id) {
        std::lock_guard<std::mutex> lock(store_mutex);
        if (items_store.erase(id) == 0) {
            return crow::response{404, R"({"error":"not found"})"};
        }
        return crow::response{204};
    });
}
