#ifndef SENSOR_REPLACEMENT_SERVICE_H
#define SENSOR_REPLACEMENT_SERVICE_H

#include "Service.h"

class SensorReplacementService : public Service {
private:
    std::string sensorType;

public:
    SensorReplacementService(int id, const std::string& name, double price, const std::string& sensorType);
    void displayInfo() const override;
    std::string getType() const override;
    std::string serialize() const override;
    std::string getSensorType() const;
};

#endif // SENSOR_REPLACEMENT_SERVICE_H