#include "AnimationManager.h"
#include "Window.h"
#include "FileManager.h"

void AnimationManager::LoadAnimationFile(const std::string& name, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return;

    AnimationsInfo currents;
    currents.name = name;
    SingleAnimationInfo current;

    const int waitingForName = 0;
    const int waitingForLoop = 1;
    const int waitingForDelay = 2;
    const int waitingForFrames = 3;

    int waitState = waitingForName;
    bool inAnimation = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.length() < 1) continue;

        if (line == ":START" && !inAnimation) {
            inAnimation = true;
            waitState = waitingForName;
            continue;
        }
        if (line == ":END" && inAnimation) {
            currents.subAnimations[current.name] = current;

            current.frames.clear();
            inAnimation = false;
            continue;
        }

        if (inAnimation) {
            if (waitState == waitingForName) {
                current.name = line;
                waitState++;
                continue;
            }
            if (waitState == waitingForLoop) {
                current.repeat = (line == "1" || line == "true");
                waitState++;
                continue;
            }
            if (waitState == waitingForDelay) {
                try {
                    current.delay = std::stoul(line);
                } catch (const std::invalid_argument& ia) {
                    Window::ThrowError("Invalid argument", ia.what());
                    current.delay = 15;
                }
                waitState++;
                continue;
            }
            if (waitState == waitingForFrames) {
                current.frames.push_back(line);
                continue;
            }
        }

    }
    file.close();

    AnimationManager::animations[name] = currents;
}

void AnimationManager::LoadAnimationFiles() {

    std::vector<std::string> files = FileManager::FilesInDirectory("assets\\anim\\", "anim");
    for (auto i : files) {
        AnimationManager::LoadAnimationFile(i, "assets\\anim\\" + i + ".anim");
    }

}

void AnimationManager::AssignAnimations(GameObject* obj, std::string animsName) {
    if (obj == nullptr) return;

    auto it = AnimationManager::animations.find(animsName);
    if (it == AnimationManager::animations.end()) return;

    AnimationsInfo found = it->second;
    for (auto const& [name, info] : found.subAnimations) {
        // SingleAnimationInfo info
        SingleAnimation* current = obj->animations.Add(name);
        current->SetLoop(info.repeat);
        current->SetDelay(info.delay);
        for (auto i : info.frames) {
            current->AddFrame(i);
        }
    }
}
