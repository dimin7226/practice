#ifndef AUTO_SERVICE_H
#define AUTO_SERVICE_H

#include "UserManager.h"
#include "ClientManager.h"
#include "ServiceManager.h"
#include "OrderManager.h"

class AutoService {
private:
    UserManager userManager;
    ClientManager clientManager;
    ServiceManager serviceManager;
    OrderManager orderManager;

    void directorMenu();
    void managerMenu();
    void createOrder(ClientManager& clientManager, ServiceManager& serviceManager, OrderManager& orderManager);
    void completeOrder(OrderManager& orderManager, ClientManager& clientManager, ServiceManager& serviceManager);
    void viewStatistics(const ClientManager& clientManager, const ServiceManager& serviceManager, const OrderManager& orderManager);
    void viewClients(const ClientManager& clientManager);
    void viewOrders(const OrderManager& orderManager, const ClientManager& clientManager, const ServiceManager& serviceManager);

public:
    AutoService();
    void run();
};

#endif // AUTO_SERVICE_H