#ifndef _RULES_H
#define _RULES_H

class Rules {

public:
    inline static int playerDeathWaitUntilRestart = 60 * 3;

    inline static int fuel = 100000;
    inline static int fuelLossOnSteering = 4;
    inline static int fuelLossOnAccelerating = 8;
    inline static bool infiniteFuel = false;

    inline static double speedOfSteering = 1.1d;
    inline static double speedOfAccelerating = 0.027d;

    //inline static double maxShipVelocity = 10.d;

    inline static bool abilityToStop = true;

    inline static bool showRadar = true;

    static void Reload();

};

#endif // _RULES_H
