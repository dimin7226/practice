#ifndef DIAGNOSTIC_SERVICE_H
#define DIAGNOSTIC_SERVICE_H

#include "Service.h"

class DiagnosticService : public Service {
private:
    std::string diagnosticType;

public:
    DiagnosticService(int id, const std::string& name, double price, const std::string& diagnosticType);
    void displayInfo() const override;
    std::string getType() const override;
    std::string serialize() const override;
    std::string getDiagnosticType() const;
};

#endif // DIAGNOSTIC_SERVICE_H