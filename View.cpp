#include "View.h"
#include "Renderer.h"
#include "World.h"
#include "Config.h"

void View::SetScale(double newScale) {
    View::scale = (newScale > 0.01d) ? newScale : 0.01d;
    View::UpdateView();
}

void View::AddScale(double amount) {
    View::SetScale(View::scale + amount);
}

void View::UpdateView() {
    View::width = Config::values.windowWidth / View::scale;
    View::height = Config::values.windowHeight / View::scale;

    View::xLeft = View::x - View::width / 2;
    View::yTop = View::y - View::height / 2;
}

void View::Move(double newX, double newY) {
    if (newX < 0.d) newX = 0.d;
    if (newY < 0.d) newY = 0.d;

    double maxX = World::width - View::width - 1;
    double maxY = World::height - View::height - 1;

    if (newX > maxX) newX = maxX;
    if (newY > maxY) newY = maxY;

    View::xLeft = newX;
    View::yTop = newY;
    View::x = newX + View::width / 2;
    View::y = newY + View::height / 2;
}

void View::MoveCenter(double newX, double newY) {
    View::Move(newX - View::width / 2, newY - View::height / 2);
}

bool View::ObjectVisible(GameObject* obj) {
    double xLeft = obj->x - (obj->width / 2);
    double yTop = obj->y - (obj->height / 2);

    double xRight = xLeft + obj->width;
    double yBottom = yTop + obj->height;

    return (xRight >= View::xLeft &&
            yBottom >= View::yTop &&
            xLeft <= View::xLeft + View::width &&
            yTop <= View::yTop + View::height);
}

SDL_Rect View::ObjectTransformTexture(GameObject* obj) {
    SDL_Rect result;

    double xLeft = obj->x - (obj->width / 2);
    double yTop = obj->y - (obj->height / 2);

    result.x = (xLeft - View::xLeft) * View::scale;
    result.y = (yTop - View::yTop) * View::scale;

    result.w = obj->width * View::scale;
    result.h = obj->height * View::scale;

    return result;
}
