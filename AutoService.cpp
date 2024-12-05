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
        std::cout << "������� ����� (��� '0' ��� ������): ";
        std::string username;
        std::cin >> username;
        if (username == "0") break;
        std::cout << "������� ������: ";
        std::string password;
        std::cin >> password;
        const User* user = userManager.authenticate(username, password);
        if (user) {
            std::cout << "����� ����������, " << user->role << "!\n";
            if (user->role == "��������") {
                directorMenu();
            }
            else if (user->role == "��������") {
                managerMenu();
            }
        }
        else {
            std::cout << "�������� ����� ��� ������. ���������� �����.\n";
        }
    }
}

void AutoService::directorMenu() {
    while (true) {
        std::cout << "\n���� ���������:\n";
        std::cout << "1. �������� ����������\n";
        std::cout << "2. �������� ���������� � ��������\n";
        std::cout << "3. �������� ���������� � �������\n";
        std::cout << "0. �����\n";
        std::cout << "�������� ��������: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "�������� ����. ���������� �����.\n";
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
            std::cout << "�������� �����. ���������� �����.\n";
        }
    }
}

void AutoService::managerMenu() {
    while (true) {
        std::cout << "\n���� ���������:\n";
        std::cout << "1. ����������� ��������\n";
        std::cout << "2. �������� ���� ��������\n";
        std::cout << "3. �������� �������\n";
        std::cout << "4. �������� ���� ��������\n";
        std::cout << "5. ���������� ������\n";
        std::cout << "6. �������� ���� �����\n";
        std::cout << "7. �������� ������\n";
        std::cout << "8. �������� ���� �����\n";
        std::cout << "9. �������� ������\n";
        std::cout << "10. �������� ���� �������\n";
        std::cout << "11. ���������� ������\n";
        std::cout << "12. �������� ������\n";
        std::cout << "13. �������� ���� �������\n";
        std::cout << "0. �����\n";
        std::cout << "�������� ��������: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "�������� ����. ���������� �����.\n";
            continue;
        }
        switch (choice) {
        case 1: {
            std::cout << "������� ��� �������: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "������� ����� �������� �������: ";
            std::string phone;
            std::getline(std::cin, phone);
            std::cout << "������� ����� �������: ";
            std::string address;
            std::getline(std::cin, address);
            std::cout << "������� ������ ���������� �������: ";
            std::string carModel;
            std::getline(std::cin, carModel);
            clientManager.addClient(name, phone, address, carModel);
            std::cout << "������ ������� ���������������.\n";
            break;
        }
        case 2:
            std::cout << "������ ���� ��������:\n";
            clientManager.displayAllClients();
            break;
        case 3: {
            std::cout << "������� ID ������� ��� ��������: ";
            int id;
            std::cin >> id;
            clientManager.removeClient(id);
            break;
        }
        case 4:
            clientManager.removeAllClients();
            break;
        case 5: {
            std::cout << "������� �������� ������: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "������� ���� ������: ";
            double price;
            std::cin >> price;
            std::cin.ignore();
            std::cout << "�������� ��� ������:\n";
            std::cout << "1. �����������\n";
            std::cout << "2. ������ �������\n";
            std::cout << "3. ������������ ���\n";
            std::cout << "������� �����: ";
            int serviceType;
            std::cin >> serviceType;
            std::string serviceTypeName;
            switch (serviceType) {
            case 1:
                serviceTypeName = "�����������";
                break;
            case 2:
                serviceTypeName = "������ �������";
                break;
            case 3:
                serviceTypeName = "������������ ���";
                break;
            default:
                std::cout << "�������� ����� ���� ������.\n";
                return;
            }
            std::cout << "������� �������������� ����������: ";
            std::string additionalInfo;
            std::cin.ignore();
            std::getline(std::cin, additionalInfo);
            serviceManager.createAndAddService(name, price, serviceTypeName, additionalInfo);
            std::cout << "������ ������� ���������.\n";
            break;
        }
        case 6:
            std::cout << "������ ���� �����:\n";
            serviceManager.displayAllServices();
            break;
        case 7: {
            std::cout << "������� ID ������ ��� ��������: ";
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
            std::cout << "������� ID ������ ��� ��������: ";
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
            std::cout << "�������� �����. ���������� �����.\n";
        }
    }
}

void AutoService::createOrder(ClientManager& clientManager, ServiceManager& serviceManager, OrderManager& orderManager) {
    std::cout << "������ ��������:\n";
    clientManager.displayAllClients();
    std::cout << "������� ID �������: ";
    int clientId;
    std::cin >> clientId;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "�������� ����. ���������� �����.\n";
        return;
    }
    const Client* client = clientManager.getClientById(clientId);
    if (!client) {
        std::cout << "������ � ����� ID �� ������.\n";
        return;
    }
    std::cout << "������ �����:\n";
    serviceManager.displayAllServices();
    std::cout << "������� ID ����� (����� ������, ��������� ���� 0): ";
    std::vector<int> serviceIds;
    int serviceId;
    while (std::cin >> serviceId && serviceId != 0) {
        if (serviceManager.getServiceById(serviceId))
            serviceIds.push_back(serviceId);
        else
            std::cout << "������ � ID " << serviceId << " �� �������.\n";
    }
    if (serviceIds.empty()) {
        std::cout << "�� ������� �� ����� ������.\n";
        return;
    }
    orderManager.addOrder(clientId, serviceIds);
    std::cout << "����� ������� ������.\n";
}

void AutoService::completeOrder(OrderManager& orderManager, ClientManager& clientManager, ServiceManager& serviceManager) {
    std::cout << "������ ������������� �������:\n";
    orderManager.displayAllOrders(clientManager, serviceManager);
    std::cout << "������� ID ������ ��� ����������: ";
    int orderId;
    std::cin >> orderId;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "�������� ����. ���������� �����.\n";
        return;
    }
    orderManager.completeOrder(orderId);
}

void AutoService::viewStatistics(const ClientManager& clientManager, const ServiceManager& serviceManager, const OrderManager& orderManager) {
    std::cout << "\n=== ���������� ����������� ===\n";
    std::cout << "����� ���������� ��������: " << clientManager.getTotalClients() << std::endl;
    std::cout << "����� ���������� �����: " << serviceManager.getTotalServices() << std::endl;
    std::cout << "����� ���������� �������: " << orderManager.getTotalOrders() << std::endl;
    int completedOrders = orderManager.getCompletedOrdersCount();
    std::cout << "����������� ������: " << completedOrders << std::endl;
    std::cout << "������ � ��������: " << (orderManager.getTotalOrders() - completedOrders) << std::endl;
    std::cout << "=== ����� ���������� ===\n";
}

void AutoService::viewClients(const ClientManager& clientManager) {
    std::cout << "\n=== ������ �������� ===\n";
    clientManager.displayAllClients();
    std::cout << "=== ����� ������ ===\n";
}

void AutoService::viewOrders(const OrderManager& orderManager, const ClientManager& clientManager, const ServiceManager& serviceManager) {
    std::cout << "\n=== ������ ������� ===\n";
    orderManager.displayAllOrders(clientManager, serviceManager);
    std::cout << "=== ����� ������ ===\n";
}