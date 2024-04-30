#include "logging.h"

int main() {
    Log *log = Log::Instance(); 
    log->message(Log::NORMAL, "program loaded");
    log->message(Log::WARNING, "program contains some problems");
    log->message(Log::ERROR, "error happens! help me!");
    log->message(Log::NORMAL, "bla-bla");
    log->message(Log::ERROR, "ohno");
    log->message(Log::NORMAL, "well");
    log->message(Log::WARNING, "need to do some fixes");
    log->message(Log::ERROR, "baaaaad");
    log->message(Log::NORMAL, "cute");
    log->message(Log::WARNING, "omg");
    log->print();
}
