#pragma once

#include "user.h"
#include "group.h"

#include <optional>

#include <sqlite3.h>

struct Mgmt {
    Mgmt(std::string sqlitePath);
    ~Mgmt();

    void createUser(std::string id, std::string name);
    void deleteUser(std::string id);
    std::vector<User> allUsers();
    std::optional<User> getUser(std::string id);

    void createGroup(std::string id);
    void deleteGroup(std::string id);
    std::vector<Group> allGroups();
    std::optional<Group> getGroup(std::string id);
    void addUser(std::string groupId, std::string userId);

private:
    void sqliteExec(std::string sql);
    std::vector<User> sqliteSelectUsers(std::string sql);
    std::vector<Group> sqliteSelectGroups(std::string sql);

private:
    sqlite3* db_;
};
