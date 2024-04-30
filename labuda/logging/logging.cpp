#include "logging.h"

#include <iostream>
#include <iomanip>

namespace {

std::ostream& operator<<(std::ostream& os, const Log::Severity& severity) {
    switch (severity) {
    case Log::NORMAL:
        os << "NORMAL";
        break;
    case Log::ERROR:
        os << "ERROR";
        break;
    case Log::WARNING:
        os << "WARNING";
        break;

    }
    return os;
}

}

Log::Log() {}

Log* Log::Instance() {
    static Log* instance = new Log();
    return instance;
}

// NOTE: not thread-safe implementation
void Log::message(Severity severity, std::string msg) {
    auto timestamp = std::chrono::system_clock::now().time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(timestamp).count();
    log_.push_back({ms, severity, msg});
}

void Log::print() {
    for (auto& record: log_) {
        auto timePoint = std::chrono::time_point<std::chrono::system_clock>{
            std::chrono::microseconds{record.microseconds}};
        auto tt = std::chrono::system_clock::to_time_t(timePoint);
        std::cout << std::put_time(std::localtime(&tt), "%F %T")
            << " " << record.severity
            << " " << record.message << std::endl;
    }
}


