#include "DiagnosticService.h"
#include <iostream>

DiagnosticService::DiagnosticService(int id, const std::string& name, double price, const std::string& diagnosticType)
    : Service(id, name, price), diagnosticType(diagnosticType) {}

void DiagnosticService::displayInfo() const {
    Service::displayInfo();
    std::cout << "��� �����������: " << diagnosticType << std::endl;
}

std::string DiagnosticService::getType() const { return "�����������"; }

std::string DiagnosticService::serialize() const {
    return Service::serialize() + "," + getType() + "," + diagnosticType;
}

std::string DiagnosticService::getDiagnosticType() const { return diagnosticType; }