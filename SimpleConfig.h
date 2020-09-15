#ifndef _SIMPLECONFIG_H
#define _SIMPLECONFIG_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <windows.h>

struct SimpleConfigValues {
    std::map<std::string, std::string> value;
};

struct SimpleConfigGroup {
    std::vector<SimpleConfigValues> no;
};

struct SimpleConfigFile {
    bool ok;
    std::map<std::string, SimpleConfigGroup> group;
};

//group["MAP"].no[0].value["width"]

class SimpleConfig {

private:
    std::ifstream* file;

public:
    SimpleConfig(std::string filename);
    virtual ~SimpleConfig();

    bool ok = false;

    SimpleConfigFile Parse();

    std::string Get(const std::string& group, const std::string number, const std::string key);


};

#endif // _SIMPLECONFIG_H
