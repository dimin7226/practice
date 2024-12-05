#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <unordered_map>
#include <string>

class UserManager {
private:
    std::unordered_map<std::string, User> users;

public:
    UserManager();
    void addUser(const std::string& username, const std::string& password, const std::string& role);
    const User* authenticate(const std::string& username, const std::string& password) const;
};

#endif // USER_MANAGER_H