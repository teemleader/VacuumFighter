#include "World.h"
#include "View.h"
#include "Renderer.h"
#include "Config.h"
#include "Keyboard.h"
#include "Physics.h"
#include <math.h>
#include "AnimationManager.h"
#include "Background.h"
#include "GUIFuel.h"
#include "GUIRadar.h"
#include "PlayerMovement.h"
#include "SimpleConfig.h"
#include "MapManager.h"

void World::Init() {
    View::SetScale(1.d); // <--------------------------

    GUIFuel::Init();

    PlayerMovement::Init(World::player);

    if (Rules::showRadar) GUIRadar::Init();
}

void World::Destroy() {
    for (auto it : World::actors) {
        delete it;
    }
    World::actors.clear();
}

void World::AddActor(GameObject* obj) {
    World::actors.push_back(obj);
}

void World::Update() {
    if (World::player != nullptr) {
        View::MoveCenter(World::player->x, World::player->y);
    }

    PlayerMovement::Update();

    if (World::player->x < 0.d || World::player->y < 0.d || World::player->x > World::width || World::player->y > World::height) {
        World::player->Destroy();
        World::restartTimer = Rules::playerDeathWaitUntilRestart;
    }

    for (std::vector<GameObject*>::iterator it = World::actors.begin(); it != World::actors.end(); it++) {
        GameObject* obj = *it;
        obj->Update();

        if (obj->Destroyed() || !obj->active) continue;

        for (std::vector<GameObject*>::iterator it2 = it+1; it2 != World::actors.end(); it2++) {
            GameObject* obj2 = *it2;
            if (obj == obj2 || obj2->Destroyed() || !obj->active) continue;
            Physics::ApplyGravity(obj, obj2);
            double collision = Physics::Collision(obj, obj2);
            if (collision > 0.d) {
                obj->colliding = true;
                obj2->colliding = true;
                if (obj == World::player || obj2 == World::player) {
                    GameObject* notPlayer = (obj == World::player) ? obj2 : obj;
                    if (Physics::CheckLanding(World::player, notPlayer, collision)) {
                        World::player->active = false;
                        World::player->mountedTo = notPlayer;
                        World::player->mountAngle = Physics::Direction(notPlayer, World::player) - Physics::Radian(notPlayer->angle);
                    } else {
                        World::player->Destroy();
                        World::restartTimer = Rules::playerDeathWaitUntilRestart;
                    }
                }
            } else {
                obj->colliding = false;
                obj2->colliding = false;
            }
        }
    }

    if (Rules::showRadar) GUIRadar::Update();

    if (World::restartTimer > 0) {
        World::restartTimer--;
        if (World::restartTimer == 0) {
            MapManager::RestartMap();
        }
    }

    //View::x += 0.2;
    //View::AddScale(-0.001);
    //View::scale -= 0.001;
}

void World::Draw() {
    Background::Draw();

    for (auto it: World::actors) {
        it->Draw();
    }

    //World::player->Draw();

    GUIFuel::Draw();
    if (Rules::showRadar) GUIRadar::Draw();
}

