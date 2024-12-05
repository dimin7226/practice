#include "Order.h"
#include <sstream>

Order::Order(int id, int clientId, const std::vector<int>& serviceIds, const std::string& date, bool completed)
    : id(id), clientId(clientId), serviceIds(serviceIds), date(date), completed(completed) {}

std::string Order::serialize() const {
    std::string result = std::to_string(id) + "," + std::to_string(clientId) + "," + date + "," + (completed ? "1" : "0");
    for (int serviceId : serviceIds)
        result += "," + std::to_string(serviceId);
    return result;
}

Order Order::deserialize(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ','))
        tokens.push_back(token);
    if (tokens.size() < 4)
        throw std::runtime_error("Неверный формат данных заказа");
    int id = std::stoi(tokens[0]);
    int clientId = std::stoi(tokens[1]);
    std::string date = tokens[2];
    bool completed = (tokens[3] == "1");
    std::vector<int> serviceIds;
    for (size_t i = 4; i < tokens.size(); ++i)
        serviceIds.push_back(std::stoi(tokens[i]));
    return Order(id, clientId, serviceIds, date, completed);
}

int Order::getId() const { return id; }
int Order::getClientId() const { return clientId; }
const std::vector<int>& Order::getServiceIds() const { return serviceIds; }
std::string Order::getDate() const { return date; }
bool Order::isCompleted() const { return completed; }
void Order::setCompleted(bool value) { completed = value; }