#include "PlayerMovement.h"
#include "Rules.h"
#include "Physics.h"
#include "GUIFuel.h"
#include "Keyboard.h"
#include "math.h"

void PlayerMovement::Init(GameObject* obj) {
    PlayerMovement::player = obj;
    PlayerMovement::havePlayer = true;
}

void PlayerMovement::Destroy() {
    PlayerMovement::player = nullptr;
    PlayerMovement::havePlayer = false;
}

GameObject* PlayerMovement::GetPlayer() {
    return PlayerMovement::player;
}

void PlayerMovement::Update() {
    if (!PlayerMovement::havePlayer || PlayerMovement::player == nullptr) return;

    if (!PlayerMovement::player->ready) return;

    if (PlayerMovement::player->Destroyed()) {
        PlayerMovement::havePlayer = false;
        return;
    }

    if (!PlayerMovement::player->active) {
        if (Keyboard::Vertical() == -1 && GUIFuel::fuel > 0) {
            PlayerMovement::player->active = true;
            PlayerMovement::player->mountedTo = nullptr;
        } else return;
    }

    if (player->colliding) return;

    if (Keyboard::Horizontal() != 0) {
        if (GUIFuel::fuel > 0) {
            PlayerMovement::player->angle += Keyboard::Horizontal() * Rules::speedOfSteering;
            GUIFuel::Drain(Rules::fuelLossOnSteering);
        }
    }

    if (Keyboard::Vertical() == -1 && GUIFuel::fuel > 0) {
        double radangle = Physics::Radian(PlayerMovement::player->angle);
        PlayerMovement::player->velX += cos(radangle) * Rules::speedOfAccelerating;
        PlayerMovement::player->velY += sin(radangle) * Rules::speedOfAccelerating;
        PlayerMovement::player->animations.Change("flying");
        GUIFuel::Drain(Rules::fuelLossOnAccelerating);
    } else {
        PlayerMovement::player->animations.Change("default");
    }

    if (Keyboard::Vertical() == 1 && Rules::abilityToStop) {
        PlayerMovement::player->velX = 0.d;
        PlayerMovement::player->velY = 0.d;
    }
}
