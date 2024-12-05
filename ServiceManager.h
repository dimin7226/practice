#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include "Service.h"
#include <vector>
#include <memory>
#include <string>

class ServiceManager {
private:
    std::vector<std::unique_ptr<Service>> services;
    std::string filename;
    int getNextId() const;

public:
    ServiceManager(const std::string& file);
    void addService(std::unique_ptr<Service> service);
    void removeService(int id);
    void removeAllServices();
    void displayAllServices() const;
    void createAndAddService(const std::string& name, double price, const std::string& type, const std::string& additionalInfo);
    const Service* getServiceById(int id) const;
    void loadServices();
    void saveServices() const;
    int getTotalServices() const;
};

#endif // SERVICE_MANAGER_H