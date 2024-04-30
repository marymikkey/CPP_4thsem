#include "mgmt.h"

#include <iostream>
#include <cassert>


void printUser(const User& user) {
    std::cout << "User " << user.id << " " << user.name << std::endl;
}

void printGroup(const Group& group) {
    std::cout << "Group " << group.id << std::endl;
    for (auto& user: group.users) {
        std::cout << "\t";
        printUser(user);
    }
}

void checkArgumentsCount(int argc, int required) {
    if (argc <= required)
        throw std::runtime_error("Not enough arguments! Required " + std::to_string(required) + " arguments");
}

int main(int argc, char** argv) {
    Mgmt mgmt("users.sqlite");


    if (argc <= 2)
        throw std::runtime_error("Not enough arguments!");
    std::string obj(argv[1]);
    std::string cmd(argv[2]);

    if (obj == "user") {
        if (cmd == "get") {
            checkArgumentsCount(argc, 3);
            if (auto user = mgmt.getUser(argv[3])) {
                printUser(*user);
            }
        } else if (cmd == "get-all") {
            for (auto& user: mgmt.allUsers()) {
                printUser(user);
            }
        } else if (cmd == "create") {
            checkArgumentsCount(argc, 4);
            mgmt.createUser(argv[3], argv[4]);
        } else if (cmd == "delete") {
            checkArgumentsCount(argc, 3);
            mgmt.deleteUser(argv[3]);
        } else {
            std::cerr << "Unexpected command " << cmd << std::endl;
            return -1;
        }
    } else if (obj == "group") {
        if (cmd == "get") {
            checkArgumentsCount(argc, 3);
            if (auto group = mgmt.getGroup(argv[3])) {
                printGroup(*group);
            }
        } else if (cmd == "get-all") {
            for (auto& group: mgmt.allGroups()) {
                printGroup(group);
            }
        } else if (cmd == "create") {
            checkArgumentsCount(argc, 3);
            mgmt.createGroup(argv[3]);
        } else if (cmd == "delete") {
            checkArgumentsCount(argc, 3);
            mgmt.deleteGroup(argv[3]);
        } else if (cmd == "add") {
            checkArgumentsCount(argc, 4);
            mgmt.addUser(argv[3], argv[4]);
        } else {
            std::cerr << "Unexpected command " << cmd << std::endl;
            return -1;
        }
    } else {
        std::cerr << "Unexpected object " << obj << std::endl;
        return -1;
    }
    return 0;
}
