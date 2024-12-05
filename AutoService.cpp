#include "AutoService.h"
#include <iostream>
#include <limits>

AutoService::AutoService()
    : clientManager("clients.txt"),
    serviceManager("services.txt"),
    orderManager("orders.txt") {
}

void AutoService::run() {
    while (true) {
        std::cout << "Введите логин (или '0' для выхода): ";
        std::string username;
        std::cin >> username;
        if (username == "0") break;
        std::cout << "Введите пароль: ";
        std::string password;
        std::cin >> password;
        const User* user = userManager.authenticate(username, password);
        if (user) {
            std::cout << "Добро пожаловать, " << user->role << "!\n";
            if (user->role == "Директор") {
                directorMenu();
            }
            else if (user->role == "Менеджер") {
                managerMenu();
            }
        }
        else {
            std::cout << "Неверный логин или пароль. Попробуйте снова.\n";
        }
    }
}

void AutoService::directorMenu() {
    while (true) {
        std::cout << "\nМеню директора:\n";
        std::cout << "1. Просмотр статистики\n";
        std::cout << "2. Просмотр информации о клиентах\n";
        std::cout << "3. Просмотр информации о заказах\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }
        switch (choice) {
        case 1:
            viewStatistics(clientManager, serviceManager, orderManager);
            break;
        case 2:
            viewClients(clientManager);
            break;
        case 3:
            viewOrders(orderManager, clientManager, serviceManager);
            break;
        case 0:
            return;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

void AutoService::managerMenu() {
    while (true) {
        std::cout << "\nМеню менеджера:\n";
        std::cout << "1. Регистрация клиентов\n";
        std::cout << "2. Просмотр всех клиентов\n";
        std::cout << "3. Удаление клиента\n";
        std::cout << "4. Удаление всех клиентов\n";
        std::cout << "5. Добавление услуги\n";
        std::cout << "6. Просмотр всех услуг\n";
        std::cout << "7. Удаление услуги\n";
        std::cout << "8. Удаление всех услуг\n";
        std::cout << "9. Создание заказа\n";
        std::cout << "10. Просмотр всех заказов\n";
        std::cout << "11. Завершение заказа\n";
        std::cout << "12. Удаление заказа\n";
        std::cout << "13. Удаление всех заказов\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }
        switch (choice) {
        case 1: {
            std::cout << "Введите имя клиента: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите номер телефона клиента: ";
            std::string phone;
            std::getline(std::cin, phone);
            std::cout << "Введите адрес клиента: ";
            std::string address;
            std::getline(std::cin, address);
            std::cout << "Введите модель автомобиля клиента: ";
            std::string carModel;
            std::getline(std::cin, carModel);
            clientManager.addClient(name, phone, address, carModel);
            std::cout << "Клиент успешно зарегистрирован.\n";
            break;
        }
        case 2:
            std::cout << "Список всех клиентов:\n";
            clientManager.displayAllClients();
            break;
        case 3: {
            std::cout << "Введите ID клиента для удаления: ";
            int id;
            std::cin >> id;
            clientManager.removeClient(id);
            break;
        }
        case 4:
            clientManager.removeAllClients();
            break;
        case 5: {
            std::cout << "Введите название услуги: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите цену услуги: ";
            double price;
            std::cin >> price;
            std::cin.ignore();
            std::cout << "Выберите тип услуги:\n";
            std::cout << "1. Диагностика\n";
            std::cout << "2. Замена датчика\n";
            std::cout << "3. Перепрошивка ЭБУ\n";
            std::cout << "Введите номер: ";
            int serviceType;
            std::cin >> serviceType;
            std::string serviceTypeName;
            switch (serviceType) {
            case 1:
                serviceTypeName = "Диагностика";
                break;
            case 2:
                serviceTypeName = "Замена датчика";
                break;
            case 3:
                serviceTypeName = "Перепрошивка ЭБУ";
                break;
            default:
                std::cout << "Неверный выбор типа услуги.\n";
                return;
            }
            std::cout << "Введите дополнительную информацию: ";
            std::string additionalInfo;
            std::cin.ignore();
            std::getline(std::cin, additionalInfo);
            serviceManager.createAndAddService(name, price, serviceTypeName, additionalInfo);
            std::cout << "Услуга успешно добавлена.\n";
            break;
        }
        case 6:
            std::cout << "Список всех услуг:\n";
            serviceManager.displayAllServices();
            break;
        case 7: {
            std::cout << "Введите ID услуги для удаления: ";
            int id;
            std::cin >> id;
            serviceManager.removeService(id);
            break;
        }
        case 8:
            serviceManager.removeAllServices();
            break;
        case 9:
            createOrder(clientManager, serviceManager, orderManager);
            break;
        case 10:
            orderManager.displayAllOrders(clientManager, serviceManager);
            break;
        case 11:
            completeOrder(orderManager, clientManager, serviceManager);
            break;
        case 12: {
            orderManager.displayAllOrders(clientManager, serviceManager);
            std::cout << "Введите ID заказа для удаления: ";
            int id;
            std::cin >> id;
            orderManager.removeOrder(id);
            break;
        }
        case 13:
            orderManager.removeAllOrders();
            break;
        case 0:
            return;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

void AutoService::createOrder(ClientManager& clientManager, ServiceManager& serviceManager, OrderManager& orderManager) {
    std::cout << "Список клиентов:\n";
    clientManager.displayAllClients();
    std::cout << "Введите ID клиента: ";
    int clientId;
    std::cin >> clientId;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Попробуйте снова.\n";
        return;
    }
    const Client* client = clientManager.getClientById(clientId);
    if (!client) {
        std::cout << "Клиент с таким ID не найден.\n";
        return;
    }
    std::cout << "Список услуг:\n";
    serviceManager.displayAllServices();
    std::cout << "Введите ID услуг (через пробел, завершите ввод 0): ";
    std::vector<int> serviceIds;
    int serviceId;
    while (std::cin >> serviceId && serviceId != 0) {
        if (serviceManager.getServiceById(serviceId))
            serviceIds.push_back(serviceId);
        else
            std::cout << "Услуга с ID " << serviceId << " не найдена.\n";
    }
    if (serviceIds.empty()) {
        std::cout << "Не выбрано ни одной услуги.\n";
        return;
    }
    orderManager.addOrder(clientId, serviceIds);
    std::cout << "Заказ успешно создан.\n";
}

void AutoService::completeOrder(OrderManager& orderManager, ClientManager& clientManager, ServiceManager& serviceManager) {
    std::cout << "Список незавершенных заказов:\n";
    orderManager.displayAllOrders(clientManager, serviceManager);
    std::cout << "Введите ID заказа для завершения: ";
    int orderId;
    std::cin >> orderId;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Попробуйте снова.\n";
        return;
    }
    orderManager.completeOrder(orderId);
}

void AutoService::viewStatistics(const ClientManager& clientManager, const ServiceManager& serviceManager, const OrderManager& orderManager) {
    std::cout << "\n=== Статистика автосервиса ===\n";
    std::cout << "Общее количество клиентов: " << clientManager.getTotalClients() << std::endl;
    std::cout << "Общее количество услуг: " << serviceManager.getTotalServices() << std::endl;
    std::cout << "Общее количество заказов: " << orderManager.getTotalOrders() << std::endl;
    int completedOrders = orderManager.getCompletedOrdersCount();
    std::cout << "Завершенные заказы: " << completedOrders << std::endl;
    std::cout << "Заказы в процессе: " << (orderManager.getTotalOrders() - completedOrders) << std::endl;
    std::cout << "=== Конец статистики ===\n";
}

void AutoService::viewClients(const ClientManager& clientManager) {
    std::cout << "\n=== Список клиентов ===\n";
    clientManager.displayAllClients();
    std::cout << "=== Конец списка ===\n";
}

void AutoService::viewOrders(const OrderManager& orderManager, const ClientManager& clientManager, const ServiceManager& serviceManager) {
    std::cout << "\n=== Список заказов ===\n";
    orderManager.displayAllOrders(clientManager, serviceManager);
    std::cout << "=== Конец списка ===\n";
}