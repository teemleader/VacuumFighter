#include "Physics.h"
#include "math.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

double Physics::Distance(GameObject* obj1, GameObject* obj2) {
    return sqrt(Physics::DistancePow(obj1, obj2));
}

double Physics::DistancePow(GameObject* obj1, GameObject* obj2) {
    double xDiff = obj1->x - obj2->x;
    double yDiff = obj1->y - obj2->y;
    return xDiff*xDiff + yDiff*yDiff;
}

double Physics::Direction(GameObject* obj1, GameObject* obj2) {
    return atan2(obj2->y - obj1->y, obj2->x - obj1->x);
}

double Physics::Gravity(GameObject* obj1, GameObject* obj2) {
    return Physics::GravitationalConstant * ((obj1->mass * obj2->mass) / (Physics::DistancePow(obj1, obj2) / 10.d));
}

void Physics::ApplyGravity(GameObject* obj1, GameObject* obj2) {
    double gravity = Physics::Gravity(obj1, obj2);
    double g1 = gravity / obj1->mass;
    double g2 = gravity / obj2->mass;

    double dir1 = Physics::Direction(obj1, obj2);
    double dir2 = Physics::Direction(obj2, obj1);

    obj1->velX += cos(dir1) * g1;
    obj1->velY += sin(dir1) * g1;

    obj2->velX += cos(dir2) * g2;
    obj2->velY += sin(dir2) * g2;
}

double Physics::Collision(GameObject* obj1, GameObject* obj2) {
    double radiuses = obj1->radius + obj2->radius;
    return (radiuses * radiuses - Physics::DistancePow(obj1, obj2));
}

double Physics::Radian(double value) {
    return value * 0.01745329252d;
}

double Physics::Degrees(double value) {
    return value * 57.2957795d;
}

bool Physics::CheckLanding(GameObject* player, GameObject* obj, double collision) {
    double dir = Physics::Degrees(Physics::Direction(obj, player));
    if (dir < 0.d) dir = 360.d + dir;

    double angle = player->angle;
    if (angle < 0.d) angle = 360.d + angle;

    double diff = dir - angle;
    if (diff < 0.d) diff = -diff;
    if (diff > 180.d) diff = 360.d - diff;

    if (diff > 40.d) return false;

    double vx = player->velX;
    if (vx < 0.d) vx = -vx;
    double vy = player->velY;
    if (vy < 0.d) vy = -vy;
    double v = vx * vx + vy * vy;

    if (v > 1.5d) return false;

    return true;
}
