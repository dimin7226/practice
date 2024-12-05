#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

class Order {
private:
    int id;
    int clientId;
    std::vector<int> serviceIds;
    std::string date;
    bool completed;

public:
    Order(int id, int clientId, const std::vector<int>& serviceIds, const std::string& date, bool completed = false);
    std::string serialize() const;
    static Order deserialize(const std::string& str);
    int getId() const;
    int getClientId() const;
    const std::vector<int>& getServiceIds() const;
    std::string getDate() const;
    bool isCompleted() const;
    void setCompleted(bool value);
};

#endif // ORDER_H