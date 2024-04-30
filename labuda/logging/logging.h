#pragma once

#include <string>
#include <chrono>
#include <vector>

class Log {
public:
    enum Severity {
        NORMAL,
        WARNING,
        ERROR
    };

public:
    Log(const Log&) = delete;
    static Log* Instance();

    void message(Severity severity, std::string msg);
    void print();

private:
    struct Record {
        int64_t microseconds;
        Severity severity;
        std::string message;
    };

    Log();

    std::vector<Record> log_;
};
