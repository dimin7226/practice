#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class Service {
protected:
    int id;
    std::string name;
    double price;

public:
    Service(int id, const std::string& name, double price);
    virtual ~Service() = default;
    virtual void displayInfo() const;
    virtual std::string getType() const = 0;
    virtual std::string serialize() const;
    int getId() const;
    std::string getName() const;
    double getPrice() const;
};

#endif // SERVICE_H