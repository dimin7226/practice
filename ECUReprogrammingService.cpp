#include "ECUReprogrammingService.h"
#include <iostream>

ECUReprogrammingService::ECUReprogrammingService(int id, const std::string& name, double price, const std::string& ecuModel)
    : Service(id, name, price), ecuModel(ecuModel) {}

void ECUReprogrammingService::displayInfo() const {
    Service::displayInfo();
    std::cout << "Модель ЭБУ: " << ecuModel << std::endl;
}

std::string ECUReprogrammingService::getType() const { return "Перепрошивка ЭБУ"; }

std::string ECUReprogrammingService::serialize() const {
    return Service::serialize() + "," + getType() + "," + ecuModel;
}

std::string ECUReprogrammingService::getECUModel() const { return ecuModel; }