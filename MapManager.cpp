#include "MapManager.h"
#include "Window.h"
#include "FileManager.h"
#include "World.h"
#include "Rules.h"

void MapManager::LoadMaps() {
    std::vector<std::string> files = FileManager::FilesInDirectory("assets\\map\\", "map");
    for (auto i : files) {
        MapManager::LoadMapFile(i, "assets\\map\\" + i + ".map");
    }
}

void MapManager::LoadMapFile(const std::string& name, const std::string& path) {
    SimpleConfig conf(path);
    if (!conf.ok) return;

    MapManager::maps[name] = conf.Parse();
}

void MapManager::StartMap(const std::string& name) {
    // if map not found
    if (MapManager::maps.find(name) == MapManager::maps.end()) return;

    MapManager::currentMap = name;

    World::Destroy();
    SimpleConfigFile c = MapManager::maps[name];

    auto val = [](SimpleConfigFile& _conf, const std::string& group, const unsigned int number, const std::string& key) {
        std::string result = "";
        if (_conf.group.find(group) != _conf.group.end()) {
            if (_conf.group[group].no.size() > number) {
                if (_conf.group[group].no[number].value.find(key) != _conf.group[group].no[number].value.end()) {
                    result = _conf.group[group].no[number].value[key];
                }
            }
        }
        return result;
    };

    World::width = std::stod(val(c, "MAP", 0, "width"));
    World::height = std::stod(val(c, "MAP", 0, "height"));

    Rules::infiniteFuel = val(c, "RULES", 0, "fuelInfinite") == "true";
    Rules::fuel = std::stoul(val(c, "RULES", 0, "fuel"));
    Rules::fuelLossOnAccelerating = std::stoul(val(c, "RULES", 0, "fuelAcelerationCost"));
    Rules::fuelLossOnSteering = std::stoul(val(c, "RULES", 0, "fuelRotationCost"));

    Rules::speedOfSteering = std::stod(val(c, "RULES", 0, "rotationSpeed"));
    Rules::speedOfAccelerating = std::stod(val(c, "RULES", 0, "accelerationSpeed"));

    Rules::abilityToStop = val(c, "RULES", 0, "canStop") == "true";
    Rules::showRadar = val(c, "RULES", 0, "showRadar") == "true";
    Rules::playerDeathWaitUntilRestart = std::stoul(val(c, "RULES", 0, "restartDelay"));

    World::player = new GameObject(val(c, "PLAYER", 0, "animation"));
    World::player->x = std::stoul(val(c, "PLAYER", 0, "x"));
    World::player->y = std::stoul(val(c, "PLAYER", 0, "y"));
    World::player->mass = std::stoul(val(c, "PLAYER", 0, "mass"));
    World::AddActor(World::player);

    unsigned int mountPlayerTo = 0;
    if (c.group.find("PLAYER") != c.group.end()) {
        if (c.group["PLAYER"].no[0].value.find("mountTo") != c.group["PLAYER"].no[0].value.end()) {
            World::player->active = false;
            mountPlayerTo = std::stoul(c.group["PLAYER"].no[0].value["mountTo"]);
        }
    }

    if (c.group.find("OBJECT") != c.group.end()) {
        unsigned int i = 1;
        for (auto v : c.group["OBJECT"].no) {
            GameObject* obj = new GameObject(v.value["animation"]);
            obj->x = std::stod(v.value["x"]);
            obj->y = std::stod(v.value["y"]);
            obj->Rotate(std::stod(v.value["rotate"]));
            obj->mass = std::stoul(v.value["mass"]);
            obj->angle = std::stod(v.value["angle"]);
            World::AddActor(obj);

            if (mountPlayerTo == i) {
                World::player->mountedTo = obj;
            }

            i++;
        }
    }

    World::Init();
}

void MapManager::RestartMap() {
    MapManager::StartMap(MapManager::currentMap);
}
