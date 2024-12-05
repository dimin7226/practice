#include "Service.h"
#include <iostream>

Service::Service(int id, const std::string& name, double price) : id(id), name(name), price(price) {}

void Service::displayInfo() const {
    std::cout << "ID: " << id << ", Название: " << name << ", Цена: " << price << " руб." << std::endl;
}

std::string Service::serialize() const {
    return std::to_string(id) + "," + name + "," + std::to_string(price);
}

int Service::getId() const { return id; }
std::string Service::getName() const { return name; }
double Service::getPrice() const { return price; }