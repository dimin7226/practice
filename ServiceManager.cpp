#include "ServiceManager.h"
#include "DiagnosticService.h"
#include "SensorReplacementService.h"
#include "ECUReprogrammingService.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

ServiceManager::ServiceManager(const std::string& file) : filename(file) {
    loadServices();
}

int ServiceManager::getNextId() const {
    if (services.empty()) return 1;
    return services.back()->getId() + 1;
}

void ServiceManager::addService(std::unique_ptr<Service> service) {
    services.push_back(std::move(service));
    saveServices();
}

void ServiceManager::removeService(int id) {
    std::cout << "Список всех услуг:\n";
    displayAllServices();
    auto it = std::remove_if(services.begin(), services.end(),
        [id](const std::unique_ptr<Service>& service) { return service->getId() == id; });
    if (it != services.end()) {
        services.erase(it, services.end());
        saveServices();
        std::cout << "Услуга с ID " << id << " удалена.\n";
    }
    else {
        std::cout << "Услуга с ID " << id << " не найдена.\n";
    }
}

void ServiceManager::removeAllServices() {
    services.clear();
    saveServices();
    std::cout << "Все услуги удалены.\n";
}

void ServiceManager::displayAllServices() const {
    const int idWidth = 5;
    const int nameWidth = 30;
    const int priceWidth = 15;
    const int typeWidth = 20;
    const int infoWidth = 30;
    auto printLine = [](int width) {
        std::cout << '+' << std::string(width, '-');
    };
    auto truncateString = [](const std::string& str, size_t width) {
        return (str.length() > width - 3) ? str.substr(0, width - 3) + "..." : str;
    };
    printLine(idWidth); printLine(nameWidth); printLine(priceWidth);
    printLine(typeWidth); printLine(infoWidth);
    std::cout << '+' << std::endl;

    std::cout << '|' << std::setw(idWidth) << "ID"
        << '|' << std::setw(nameWidth) << "Название"
        << '|' << std::setw(priceWidth) << "Цена"
        << '|' << std::setw(typeWidth) << "Тип"
        << '|' << std::setw(infoWidth) << "Доп. информация"
        << '|' << std::endl;
    printLine(idWidth); printLine(nameWidth); printLine(priceWidth);
    printLine(typeWidth); printLine(infoWidth);
    std::cout << '+' << std::endl;
    for (const auto& service : services) {
        std::string additionalInfo;
        if (auto* diag = dynamic_cast<const DiagnosticService*>(service.get()))
            additionalInfo = diag->getDiagnosticType();
        else if (auto* sensor = dynamic_cast<const SensorReplacementService*>(service.get()))
            additionalInfo = sensor->getSensorType();
        else if (auto* ecu = dynamic_cast<const ECUReprogrammingService*>(service.get()))
            additionalInfo = ecu->getECUModel();
        std::cout << '|' << std::setw(idWidth) << service->getId()
            << '|' << std::setw(nameWidth) << truncateString(service->getName(), nameWidth)
            << '|' << std::setw(priceWidth) << service->getPrice()
            << '|' << std::setw(typeWidth) << truncateString(service->getType(), typeWidth)
            << '|' << std::setw(infoWidth) << truncateString(additionalInfo, infoWidth)
            << '|' << std::endl;
    }
    printLine(idWidth); printLine(nameWidth); printLine(priceWidth);
    printLine(typeWidth); printLine(infoWidth);
    std::cout << '+' << std::endl;
}

void ServiceManager::createAndAddService(const std::string& name, double price, const std::string& type, const std::string& additionalInfo) {
    int id = getNextId();
    std::unique_ptr<Service> service;
    if (type == "Диагностика")
        service = std::make_unique<DiagnosticService>(id, name, price, additionalInfo);
    else if (type == "Замена датчика")
        service = std::make_unique<SensorReplacementService>(id, name, price, additionalInfo);
    else if (type == "Перепрошивка ЭБУ")
        service = std::make_unique<ECUReprogrammingService>(id, name, price, additionalInfo);
    else
        throw std::runtime_error("Неизвестный тип услуги");
    try {
        addService(std::move(service));
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при добавлении услуги: " << e.what() << std::endl;
    }
}

const Service* ServiceManager::getServiceById(int id) const {
    auto it = std::find_if(services.begin(), services.end(),
        [id](const std::unique_ptr<Service>& service) { return service->getId() == id; });
    return it != services.end() ? it->get() : nullptr;
}

void ServiceManager::loadServices() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    services.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ','))
            tokens.push_back(token);
        if (tokens.size() < 5) {
            std::cerr << "Неверный формат данных услуги: " << line << std::endl;
            continue;
        }
        int id = std::stoi(tokens[0]);
        std::string name = tokens[1];
        double price = std::stod(tokens[2]);
        std::string type = tokens[3];
        std::string additionalInfo = tokens[4];
        if (type == "Диагностика")
            services.push_back(std::make_unique<DiagnosticService>(id, name, price, additionalInfo));
        else if (type == "Замена датчика")
            services.push_back(std::make_unique<SensorReplacementService>(id, name, price, additionalInfo));
        else if (type == "Перепрошивка ЭБУ")
            services.push_back(std::make_unique<ECUReprogrammingService>(id, name, price, additionalInfo));
        else
            std::cerr << "Неизвестный тип услуги: " << type << std::endl;
    }
    file.close();
}

void ServiceManager::saveServices() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }
    for (const auto& service : services)
        file << service->serialize() << std::endl;
    file.close();
}

int ServiceManager::getTotalServices() const {
    return services.size();
}