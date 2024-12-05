#include "OrderManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <sstream>

OrderManager::OrderManager(const std::string& file) : filename(file) {
    loadOrders();
}

int OrderManager::getNextId() const {
    if (orders.empty()) return 1;
    return orders.back().getId() + 1;
}

void OrderManager::addOrder(int clientId, const std::vector<int>& serviceIds) {
    int id = getNextId();
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    std::ostringstream oss;
    oss << std::put_time(&now, "%Y-%m-%d");
    orders.emplace_back(id, clientId, serviceIds, oss.str());
    saveOrders();
}

void OrderManager::loadOrders() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    orders.clear();
    std::string line;
    while (std::getline(file, line)) {
        try {
            orders.push_back(Order::deserialize(line));
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при чтении данных заказа: " << e.what() << std::endl;
        }
    }
    file.close();
}

void OrderManager::saveOrders() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }
    for (const auto& order : orders)
        file << order.serialize() << std::endl;
    file.close();
}

void OrderManager::removeOrder(int id) {
    auto it = std::remove_if(orders.begin(), orders.end(),
        [id](const Order& order) { return order.getId() == id; });
    if (it != orders.end()) {
        orders.erase(it, orders.end());
        saveOrders();
        std::cout << "Заказ с ID " << id << " удален.\n";
    }
    else {
        std::cout << "Заказ с ID " << id << " не найден.\n";
    }
}

void OrderManager::completeOrder(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](const Order& order) { return order.getId() == orderId; });
    if (it != orders.end()) {
        it->setCompleted(true);
        saveOrders();
        std::cout << "Заказ с ID " << orderId << " завершен.\n";
    }
    else {
        std::cout << "Заказ с ID " << orderId << " не найден.\n";
    }
}

void OrderManager::removeAllOrders() {
    orders.clear();
    saveOrders();
    std::cout << "Все заказы удалены.\n";
}

void OrderManager::displayAllOrders(const ClientManager& clientManager, const ServiceManager& serviceManager) const {
    std::cout << "Список заказов:\n";
    const int idWidth = 5;
    const int clientWidth = 30;
    const int dateWidth = 15;
    const int statusWidth = 15;
    const int servicesWidth = 30;

    auto printLine = [](int width) {
        std::cout << '+' << std::string(width, '-');
    };

    auto truncateString = [](const std::string& str, size_t width) {
        return (str.length() > width - 3) ? str.substr(0, width - 3) + "..." : str;
    };

    printLine(idWidth); printLine(clientWidth); printLine(dateWidth);
    printLine(statusWidth); printLine(servicesWidth);
    std::cout << '+' << std::endl;

    std::cout << '|' << std::setw(idWidth) << "ID"
        << '|' << std::setw(clientWidth) << "Клиент"
        << '|' << std::setw(dateWidth) << "Дата"
        << '|' << std::setw(statusWidth) << "Статус"
        << '|' << std::setw(servicesWidth) << "Услуги"
        << '|' << std::endl;

    printLine(idWidth); printLine(clientWidth); printLine(dateWidth);
    printLine(statusWidth); printLine(servicesWidth);
    std::cout << '+' << std::endl;

    for (const auto& order : orders) {
        const Client* client = clientManager.getClientById(order.getClientId());
        std::string clientName = client ? client->getName() : "Неизвестно";
        std::string status = order.isCompleted() ? "Выполнен" : "В процессе";

        std::string services;
        for (int serviceId : order.getServiceIds()) {
            const Service* service = serviceManager.getServiceById(serviceId);
            if (service) {
                if (!services.empty()) services += ", ";
                services += service->getName();
            }
        }

        std::cout << '|' << std::setw(idWidth) << order.getId()
            << '|' << std::setw(clientWidth) << truncateString(clientName, clientWidth)
            << '|' << std::setw(dateWidth) << order.getDate()
            << '|' << std::setw(statusWidth) << status
            << '|' << std::setw(servicesWidth) << truncateString(services, servicesWidth)
            << '|' << std::endl;
    }

    printLine(idWidth); printLine(clientWidth); printLine(dateWidth);
    printLine(statusWidth); printLine(servicesWidth);
    std::cout << '+' << std::endl;
}

int OrderManager::getTotalOrders() const {
    return orders.size();
}

int OrderManager::getCompletedOrdersCount() const {
    return std::count_if(orders.begin(), orders.end(), [](const Order& order) { return order.isCompleted(); });
}