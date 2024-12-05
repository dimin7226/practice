#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "Order.h"
#include "ClientManager.h"
#include "ServiceManager.h"
#include <vector>
#include <string>

class OrderManager {
private:
    std::vector<Order> orders;
    std::string filename;
    int getNextId() const;

public:
    OrderManager(const std::string& file);
    void addOrder(int clientId, const std::vector<int>& serviceIds);
    void loadOrders();
    void saveOrders() const;
    void removeOrder(int id);
    void completeOrder(int orderId);
    void removeAllOrders();
    void displayAllOrders(const ClientManager& clientManager, const ServiceManager& serviceManager) const;
    int getTotalOrders() const;
    int getCompletedOrdersCount() const;
};

#endif // ORDER_MANAGER_H