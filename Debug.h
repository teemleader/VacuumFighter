#ifndef _DEBUG_H
#define _DEBUG_H

#define DEBUGGING

static void Debug(std::string msg) {
    #ifdef DEBUGGING
    std::cout << msg << std::endl;
    #endif
}

static void Debug(long msg) {
    #ifdef DEBUGGING
    std::cout << msg << std::endl;
    #endif
}

static void Debug(double msg) {
    #ifdef DEBUGGING
    std::cout << msg << std::endl;
    #endif
}

static void Debug(bool value) {
    #ifdef DEBUGGING
    std::string msg = (value) ? "true" : "false";
    std::cout << msg  << std::endl;
    #endif
}

static void Debug(std::string msg, std::string value) {
    #ifdef DEBUGGING
    std::cout << msg << ": '" << value << "'" << std::endl;
    #endif
}

static void Debug(std::string msg, long value) {
    #ifdef DEBUGGING
    std::cout << msg << ": '" << value << "'" << std::endl;
    #endif
}

static void Debug(std::string msg, double value) {
    #ifdef DEBUGGING
    std::cout << msg << ": '" << value << "'" << std::endl;
    #endif
}

static void Debug(std::string msg, bool value) {
    #ifdef DEBUGGING
    std::string val = (value) ? "true" : "false";
    std::cout << msg << ": '" << val << "'" << std::endl;
    #endif
}

#endif
