#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "Client.h"
#include <vector>
#include <string>

class ClientManager {
private:
    std::vector<Client> clients;
    std::string filename;
    int getNextId() const;

public:
    ClientManager(const std::string& file);
    void addClient(const std::string& name, const std::string& phone, const std::string& address, const std::string& carModel);
    const Client* getClientById(int id) const;
    void loadClients();
    void removeClient(int id);
    void removeAllClients();
    void displayAllClients() const;
    void saveClients() const;
    int getTotalClients() const;
};

#endif // CLIENT_MANAGER_H