#include "mgmt.h"

#include <stdexcept>
#include <sstream>
#include <cassert>
#include <iostream>
#include <unordered_map>


Mgmt::Mgmt(std::string sqlitePath)
{
    auto rc = sqlite3_open(sqlitePath.data(), &db_);
    if (rc) {
        sqlite3_close(db_);
        throw std::runtime_error("Cannot open sqlite db " + sqlitePath);
    }
}

Mgmt::~Mgmt() {
    sqlite3_close(db_);
}

void Mgmt::sqliteExec(std::string sql) {
    char* errMsg;
    if (SQLITE_OK != sqlite3_exec(db_, sql.data(), NULL, NULL, &errMsg)) {//функция для выполнения запроса
        std::string msg(errMsg);
        sqlite3_free(errMsg);//от утечки
        throw std::runtime_error("Sqlite error: " + msg);
    }
}

std::vector<User> Mgmt::sqliteSelectUsers(std::string sql) {
    auto callback = [](void *usersVec, int argc, char **argv, char **azColName) {//лямбда - функц сишная для скл
        auto users = static_cast<std::vector<User>*>(usersVec);//кастим указатель к вектору
        assert(users);
        users->push_back({argv[0], argv[1]});//айди и имя - лист инициализвации ю = {ид, имя}
        return 0;
    };
    std::vector<User> users;
    char* errMsg;
    if (SQLITE_OK != sqlite3_exec(db_, sql.data(), callback, &users, &errMsg)) {//callback - функция, которая вызывается склем на каждую стр выходных данных
        std::string msg(errMsg);
        sqlite3_free(errMsg);
        throw std::runtime_error("Sqlite error: " + msg);
    }
    return users;
}

std::vector<Group> Mgmt::sqliteSelectGroups(std::string sql) {
    auto callback = [](void *groupsMap, int argc, char **argv, char **azColName) {
        auto groups = static_cast<std::unordered_map<std::string, std::vector<User>>*>(groupsMap);
        assert(groups);
        (*groups)[argv[0]].push_back({argv[1], argv[2]});//ссылка на значение, создаст пустой вектор
        return 0;
    };
    std::unordered_map<std::string, std::vector<User>> groups;
    char* errMsg;
    if (SQLITE_OK != sqlite3_exec(db_, sql.data(), callback, &groups, &errMsg)) {
        std::string msg(errMsg);
        sqlite3_free(errMsg);
        throw std::runtime_error("Sqlite error: " + msg);
    }
    std::vector<Group> groupsVec;
    for (const auto& [groupId, users]: groups) {//k-value
        groupsVec.push_back({groupId, users});
    }
    return groupsVec;
}

void Mgmt::createUser(std::string id, std::string name) {
    std::ostringstream ss;//класс для записи потока в строку
    ss << "insert into user (id, name)";
    ss << " values ('" << id << "', '" << name << "')";
    ss << " on conflict (id) do update set name=excluded.name";
    sqliteExec(ss.str());
}

void Mgmt::deleteUser(std::string id) {
    std::ostringstream ss;
    ss << "delete from user_group where user = '" << id << "';";//из групп дел
    ss << "delete from user where id = '" << id << "';";
    sqliteExec(ss.str());
}

std::vector<User> Mgmt::allUsers() {
    return sqliteSelectUsers("select id, name from user");
}

std::optional<User> Mgmt::getUser(std::string id) {
    std::ostringstream sql;
    sql << "select id, name from user where id = '" << id << "'";
    auto users = sqliteSelectUsers(sql.str());
    assert(users.size() <= 1);

        
    return users.size()//преобр юзерс в опшнл
        ? std::optional(users[0])
        : std::nullopt;
}

void Mgmt::createGroup(std::string id) {
    std::ostringstream ss;
    ss << "insert into \"group\" (id)";
    ss << " values ('" << id << "')";
    ss << " on conflict do nothing";
    sqliteExec(ss.str());
}

void Mgmt::deleteGroup(std::string id) {
    std::ostringstream ss;
    ss << "delete from user_group where \"group\" = '" << id << "';";
    sqliteExec(ss.str());
}

void Mgmt::addUser(std::string groupId, std::string userId) {
    std::ostringstream sql;
    sql << "insert into user_group(\"group\", user)";
    sql << " values ('" << groupId << "', '" << userId << "')";
    sql << " on conflict do nothing";
    sqliteExec(sql.str());
}

std::vector<Group> Mgmt::allGroups() {
    std::ostringstream sql;
    sql << "select ug.\"group\", u.id, u.name";//alias
    sql << " from user_group ug";
    sql << " join user u on u.id = ug.user";
    return sqliteSelectGroups(sql.str());
}

std::optional<Group> Mgmt::getGroup(std::string id) {
    std::ostringstream sql;
    sql << "select ug.\"group\", u.id, u.name";
    sql << " from user_group ug";
    sql << " join user u on u.id = ug.user";
    sql << " where ug.\"group\" = '" << id << "'";
    auto groups = sqliteSelectGroups(sql.str());
    assert(groups.size() <= 1);
        
    return groups.size()
        ? std::optional(groups[0])
        : std::nullopt;
}

