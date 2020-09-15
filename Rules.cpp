#include "Rules.h"
#include "GUIFuel.h"

void Rules::Reload() {
    GUIFuel::fuelMax = Rules::fuel;
    GUIFuel::fuel = Rules::fuel;
}
