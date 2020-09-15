#include "GUIRadar.h"
#include "World.h"
#include "Config.h"
#include "View.h"
#include "Window.h"
#include "PlayerMovement.h"

void GUIRadar::Init() {
    if (GUIRadar::renderTexture != nullptr) return;

    GUIRadar::renderTexture = SDL_CreateTexture(Renderer::GetHandle(), SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, GUIRadar::radarWidth, GUIRadar::radarHeight);
}

void GUIRadar::Draw() {
    SDL_SetRenderTarget(Renderer::GetHandle(), GUIRadar::renderTexture);
	SDL_RenderClear(Renderer::GetHandle());

    for (auto it: World::actors) {
        it->DrawOnRadar();
    }

    SDL_SetRenderTarget(Renderer::GetHandle(), nullptr);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = GUIRadar::radarWidth;
    src.h = GUIRadar::radarHeight;

    SDL_Rect rect;
    rect.x = GUIRadar::radarX;
    rect.y = GUIRadar::radarY;
    rect.w = GUIRadar::radarWidth;
    rect.h = GUIRadar::radarHeight;

    Renderer::DrawTexture(GUIRadar::renderTexture, &src, &rect, 0);

    Renderer::DrawRectangle(rect, 255, 255, 255, 255);
}

void GUIRadar::Update() {
    GUIRadar::viewWidth = (double)Config::values.windowWidth / GUIRadar::scale;
    GUIRadar::viewHeight = (double)Config::values.windowWidth / GUIRadar::scale;

    double tempViewXLeft = View::x - GUIRadar::viewWidth / 2;
    double tempViewYTop = View::y - GUIRadar::viewHeight / 2;

    GUIRadar::viewXLeft = tempViewXLeft;
    GUIRadar::viewYTop = tempViewYTop;
}

SDL_Rect GUIRadar::ObjectTransformTexture(GameObject* obj) {
    SDL_Rect result;

    double xLeft = obj->x - (obj->width / 2);
    double yTop = obj->y - (obj->height / 2);
    double realScale = (double)GUIRadar::radarWidth / GUIRadar::viewWidth;

    result.x = (xLeft - GUIRadar::viewXLeft) * realScale;
    result.y = (yTop - GUIRadar::viewYTop) * realScale;

    result.w = obj->width * realScale;
    result.h = obj->height * realScale;

    return result;
}

bool GUIRadar::ObjectVisible(GameObject* obj) {
    double xLeft = obj->x - (obj->width / 2);
    double yTop = obj->y - (obj->height / 2);
    return (
        xLeft + obj->width >= GUIRadar::viewXLeft &&
        yTop + obj->height >= GUIRadar::viewYTop &&
        xLeft <= GUIRadar::viewXLeft + GUIRadar::viewWidth &&
        yTop <= GUIRadar::viewYTop + GUIRadar::viewHeight
    );
}
