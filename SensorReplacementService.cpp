#include "SensorReplacementService.h"
#include <iostream>

SensorReplacementService::SensorReplacementService(int id, const std::string& name, double price, const std::string& sensorType)
    : Service(id, name, price), sensorType(sensorType) {}

void SensorReplacementService::displayInfo() const {
    Service::displayInfo();
    std::cout << "Тип датчика: " << sensorType << std::endl;
}

std::string SensorReplacementService::getType() const { return "Замена датчика"; }

std::string SensorReplacementService::serialize() const {
    return Service::serialize() + "," + getType() + "," + sensorType;
}

std::string SensorReplacementService::getSensorType() const { return sensorType; }