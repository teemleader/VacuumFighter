#ifndef _PLAYERMOVEMENT_H
#define _PLAYERMOVEMENT_H

#include "GameObject.h"

class PlayerMovement {

private:
    inline static GameObject* player = nullptr;
    inline static bool havePlayer = false;

public:
    static void Init(GameObject* obj);
    static void Destroy();

    static void Update();
    static GameObject* GetPlayer();


};

#endif // _PLAYERMOVEMENT_H
