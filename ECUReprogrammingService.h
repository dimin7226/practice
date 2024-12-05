#ifndef ECU_REPROGRAMMING_SERVICE_H
#define ECU_REPROGRAMMING_SERVICE_H

#include "Service.h"

class ECUReprogrammingService : public Service {
private:
    std::string ecuModel;

public:
    ECUReprogrammingService(int id, const std::string& name, double price, const std::string& ecuModel);
    void displayInfo() const override;
    std::string getType() const override;
    std::string serialize() const override;
    std::string getECUModel() const;
};

#endif // ECU_REPROGRAMMING_SERVICE_H