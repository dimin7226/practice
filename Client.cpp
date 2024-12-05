#include "Client.h"
#include <sstream>
#include <vector>

Client::Client(int id, const std::string& name, const std::string& phone, const std::string& address, const std::string& carModel)
    : id(id), name(name), phone(phone), address(address), carModel(carModel) {}

std::string Client::serialize() const {
    return std::to_string(id) + "," + name + "," + phone + "," + address + "," + carModel;
}

Client Client::deserialize(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) tokens.push_back(token);
    if (tokens.size() != 5)
        throw std::runtime_error("Неверный формат данных клиента");
    return Client(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4]);
}

int Client::getId() const { return id; }
std::string Client::getName() const { return name; }
std::string Client::getPhone() const { return phone; }
std::string Client::getAddress() const { return address; }
std::string Client::getCarModel() const { return carModel; }