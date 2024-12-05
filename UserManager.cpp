#include "UserManager.h"

UserManager::UserManager() {
    addUser("director", "directorpass", "Директор");
    addUser("manager", "managerpass", "Менеджер");
}

void UserManager::addUser(const std::string& username, const std::string& password, const std::string& role) {
    users[username] = { username, password, role };
}

const User* UserManager::authenticate(const std::string& username, const std::string& password) const {
    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        return &it->second;
    }
    return nullptr;
}