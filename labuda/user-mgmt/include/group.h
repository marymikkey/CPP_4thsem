#pragma once

#include <string>
#include <vector>

#include "user.h"

struct Group {
    std::string id;
    std::vector<User> users;
};
