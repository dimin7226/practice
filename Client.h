#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    int id;
    std::string name;
    std::string phone;
    std::string address;
    std::string carModel;

public:
    Client(int id, const std::string& name, const std::string& phone, const std::string& address, const std::string& carModel);
    std::string serialize() const;
    static Client deserialize(const std::string& str);
    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getAddress() const;
    std::string getCarModel() const;
};

#endif // CLIENT_H