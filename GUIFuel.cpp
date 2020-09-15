#include "GUIFuel.h"

#include "TextureManager.h"
#include "Renderer.h"
#include "Window.h"
#include "Rules.h"

void GUIFuel::Init() {
    GUIFuel::fuelMax = Rules::fuel;
    GUIFuel::fuel = Rules::fuel;
}

void GUIFuel::Drain(unsigned int amount) {
    if (Rules::infiniteFuel) return;

    GUIFuel::fuel -= amount;
    if (GUIFuel::fuel < 0) GUIFuel::fuel = 0;
}

void GUIFuel::Draw() {
    SDL_Texture* fuel = TextureManager::Get("fuel");
    SDL_Rect fuelRect = TextureManager::GetSourceRect("fuel");

    SDL_Texture* fuelover = TextureManager::Get("fuelover");
    SDL_Rect fueloverRect = TextureManager::GetSourceRect("fuelover");

    const double yDiff = (fueloverRect.h - fuelRect.h) / 2;

    const double fuelHeight = ((double)GUIFuel::fuel / (double)GUIFuel::fuelMax) * fuelRect.h;
    const double fuelPlusY = yDiff + (fuelRect.h - fuelHeight);

    SDL_Rect fuelDest;
    fuelDest.x = GUIFuel::x;
    fuelDest.y = GUIFuel::y + fuelPlusY;
    fuelDest.w = fuelRect.w;
    fuelDest.h = fuelHeight;

    Renderer::DrawTexture(fuel, &fuelRect, &fuelDest, 0.d);

    SDL_Rect fueloverDest;
    fueloverDest.x = GUIFuel::x;
    fueloverDest.y = GUIFuel::y;
    fueloverDest.w = fueloverRect.w;
    fueloverDest.h = fueloverRect.h;

    Renderer::DrawTexture(fuelover, &fueloverRect, &fueloverDest, 0.d);
}
