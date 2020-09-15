#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "GameObject.h"

class Physics {

private:
    inline static const double GravitationalConstant = 0.0018d;

public:
    static double Distance(GameObject* obj1, GameObject* obj2);
    static double DistancePow(GameObject* obj1, GameObject* obj2);
    static double Direction(GameObject* obj1, GameObject* obj2);
    static double Gravity(GameObject* obj1, GameObject* obj2);
    static void ApplyGravity(GameObject* obj1, GameObject* obj2);

    static double Collision(GameObject* obj1, GameObject* obj2);
    static bool CheckLanding(GameObject* player, GameObject* obj, double collision);

    static double Radian(double value);
    static double Degrees(double value);


};

#endif // _PHYSICS_H
