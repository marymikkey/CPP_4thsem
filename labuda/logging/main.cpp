#include "logging.h"

int main() {
    Log *log = Log::Instance(); 
    log->message(Log::NORMAL, "program loaded");
    log->message(Log::ERROR, "error happens! help me!");
    log->print(); 
}
