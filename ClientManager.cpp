#include "ClientManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

ClientManager::ClientManager(const std::string& file) : filename(file) {
    loadClients();
}

int ClientManager::getNextId() const {
    if (clients.empty()) return 1;
    return clients.back().getId() + 1;
}

void ClientManager::addClient(const std::string& name, const std::string& phone, const std::string& address, const std::string& carModel) {
    int id = getNextId();
    clients.emplace_back(id, name, phone, address, carModel);
    saveClients();
}

const Client* ClientManager::getClientById(int id) const {
    auto it = std::find_if(clients.begin(), clients.end(),
        [id](const Client& client) { return client.getId() == id; });
    return it != clients.end() ? &(*it) : nullptr;
}

void ClientManager::loadClients() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    clients.clear();
    std::string line;
    while (std::getline(file, line)) {
        try {
            clients.push_back(Client::deserialize(line));
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при чтении данных клиента: " << e.what() << std::endl;
        }
    }
    file.close();
}

void ClientManager::removeClient(int id) {
    std::cout << "Список всех клиентов:\n";
    displayAllClients();
    auto it = std::remove_if(clients.begin(), clients.end(),
        [id](const Client& client) { return client.getId() == id; });
    if (it != clients.end()) {
        clients.erase(it, clients.end());
        saveClients();
        std::cout << "Клиент с ID " << id << " удален.\n";
    }
    else {
        std::cout << "Клиент с ID " << id << " не найден.\n";
    }
}

void ClientManager::removeAllClients() {
    clients.clear();
    saveClients();
    std::cout << "Все клиенты удалены.\n";
}

void ClientManager::displayAllClients() const {
    const int idWidth = 5;
    const int nameWidth = 30;
    const int phoneWidth = 15;
    const int addressWidth = 30;
    const int carModelWidth = 20;

    auto printLine = [](int width) {
        std::cout << '+' << std::string(width, '-');
    };

    auto truncateString = [](const std::string& str, size_t width) {
        return (str.length() > width - 3) ? str.substr(0, width - 3) + "..." : str;
    };

    printLine(idWidth); printLine(nameWidth); printLine(phoneWidth);
    printLine(addressWidth); printLine(carModelWidth);
    std::cout << '+' << std::endl;

    std::cout << '|' << std::setw(idWidth) << "ID"
        << '|' << std::setw(nameWidth) << "Имя"
        << '|' << std::setw(phoneWidth) << "Телефон"
        << '|' << std::setw(addressWidth) << "Адрес"
        << '|' << std::setw(carModelWidth) << "Модель авто"
        << '|' << std::endl;

    printLine(idWidth); printLine(nameWidth); printLine(phoneWidth);
    printLine(addressWidth); printLine(carModelWidth);
    std::cout << '+' << std::endl;

    for (const auto& client : clients) {
        std::cout << '|' << std::setw(idWidth) << client.getId()
            << '|' << std::setw(nameWidth) << truncateString(client.getName(), nameWidth)
            << '|' << std::setw(phoneWidth) << truncateString(client.getPhone(), phoneWidth)
            << '|' << std::setw(addressWidth) << truncateString(client.getAddress(), addressWidth)
            << '|' << std::setw(carModelWidth) << truncateString(client.getCarModel(), carModelWidth)
            << '|' << std::endl;
    }

    printLine(idWidth); printLine(nameWidth); printLine(phoneWidth);
    printLine(addressWidth); printLine(carModelWidth);
    std::cout << '+' << std::endl;
}

void ClientManager::saveClients() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }
    for (const auto& client : clients)
        file << client.serialize() << std::endl;
    file.close();
}

int ClientManager::getTotalClients() const {
    return clients.size();
}