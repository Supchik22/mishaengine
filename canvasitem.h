#ifndef CANVASITEM_H
#define CANVASITEM_H

#include "game.h"
#include <algorithm>

class CanvasItem {
public:
    float offsetX, offsetY;
    bool visible;

    CanvasItem() : offsetX(0.0f), offsetY(0.0f), visible(true) {}
    virtual ~CanvasItem() {}

    virtual void update() = 0;
    virtual void draw() = 0;

    void move(float dx, float dy) {
        offsetX += dx;
        offsetY += dy;
    }

    void show() {
        visible = true;
    }

    void hide() {
        visible = false;
    }

    void free() {
        Game& game = Game::getInstance();
        auto& canvasItems = game.getCanvasItems();

        // Пошук і видалення поточного об'єкта з вектора
        auto it = std::find(canvasItems.begin(), canvasItems.end(), this);
        if (it != canvasItems.end()) {
            canvasItems.erase(it);
        }

        // Видалення самого об'єкта
        delete this;
    }

};

#endif // CANVASITEM_H
