#include "SimpleConfig.h"

SimpleConfig::SimpleConfig(std::string filename) {
    this->ok = false;

    this->file = new std::ifstream(filename);
    if (file->is_open()) this->ok = true;
}

SimpleConfig::~SimpleConfig() {
    delete this->file;
}

SimpleConfigFile SimpleConfig::Parse() {
    SimpleConfigFile result;
    result.ok = false;

    if (!this->ok) return result;

    bool inGroup = false;
    std::string currentGroupName = "";
    unsigned int currentGroupNum;
    std::map<std::string, int> groupCount;

    auto newGroup = [](const std::string& gName, std::map<std::string, int>& gMap, SimpleConfigFile& res) {
        int n = 0;
        if (gMap.find(gName) != gMap.end()) {
            n = gMap[gName];
            SimpleConfigValues tempV;
            res.group[gName].no.insert(res.group[gName].no.begin() + n, tempV);
        } else {
            SimpleConfigGroup temp;
            res.group[gName] = temp;
            SimpleConfigValues tempV;
            res.group[gName].no.insert(res.group[gName].no.begin() + n, tempV);
        }

        gMap[gName] = n + 1;
        return n;
    };

    auto startsWith = [](const std::string& str, const std::string& v) {
        if (str.substr(0, v.length()) == v) {
            return str.substr(v.length(), std::string::npos);
        }
        return std::string("");
    };

    struct _keyvalue{
        std::string key;
        std::string value;
    };

    auto parseKeyValue = [](const std::string& str) {
        _keyvalue kv = {"", ""};
        std::size_t found = str.find("=");
        if (found != std::string::npos) {
            kv.key = str.substr(0, found);
            if (found + 1 < str.length()) {
                kv.value = str.substr(found + 1, std::string::npos);
            }
        }
        return kv;
    };

    std::string line;
    while (std::getline(*this->file, line)) {
        if (line.length() < 1) continue;

        std::string group_name = startsWith(line, ":");
        if (group_name.length() != 0) {
            if (group_name == "END") {
                inGroup = false;
                currentGroupName = "";
            } else {
                inGroup = true;
                currentGroupName = group_name;
                currentGroupNum = newGroup(currentGroupName, groupCount, result);
            }
        }

        if (inGroup) {
            _keyvalue kv = parseKeyValue(line);
            if (kv.key.length() > 0 && kv.value.length() > 0) {
                result.group[currentGroupName].no[currentGroupNum].value[kv.key] = kv.value;
            }
        }
    }

    this->file->close();

    result.ok = false;
    return result;
}
