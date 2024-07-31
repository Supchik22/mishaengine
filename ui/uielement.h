#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "../canvasitem.h"
#include <functional>
#include <GL/glut.h>

enum class Align {
    LEFT,
    CENTER,
    RIGHT
};

enum class ScreenPosition {
    LEFT,
    CENTER,
    TOP,
    BOTTOM,
    RIGHT
};

class UIElement : public CanvasItem {
public:
    Align align;  // Вирівнювання
    ScreenPosition screenPosition; // Позиція на екрані
    bool isHud;
    float offsetX, offsetY; // Зсуви
    float rectX, rectY, rectWidth, rectHeight; // Розмір та позиція елемента

    UIElement(Align align, ScreenPosition screenPosition, float offsetX, float offsetY, float rectX, float rectY, float rectWidth, float rectHeight)
        : align(align), screenPosition(screenPosition), offsetX(offsetX), offsetY(offsetY), rectX(rectX), rectY(rectY), rectWidth(rectWidth), rectHeight(rectHeight), isHud(true)
    {}

    virtual ~UIElement() {}

    virtual void update() override {
        // Реалізуйте оновлення UI елемента
    }

    virtual void draw() override {

    }

    bool isClicked(float mouseX, float mouseY) const {
        float x = rectX + offsetX;
        float y = rectY + offsetY;

        switch (screenPosition) {
            case ScreenPosition::LEFT:
                x = -1.0f + offsetX;
                break;
            case ScreenPosition::CENTER:
                x = -rectWidth / 2.0f + offsetX;
                break;
            case ScreenPosition::RIGHT:
                x = 1.0f - rectWidth + offsetX;
                break;
            case ScreenPosition::TOP:
                y = 1.0f - rectHeight + offsetY;
                break;
            case ScreenPosition::BOTTOM:
                y = -1.0f + offsetY;
                break;
        }

        switch (align) {
            case Align::LEFT:
                // x is already adjusted
                break;
            case Align::CENTER:
                x -= rectWidth / 2.0f;
                break;
            case Align::RIGHT:
                x -= rectWidth;
                break;
        }

        return mouseX >= x && mouseX <= x + rectWidth &&
               mouseY >= y && mouseY <= y + rectHeight;
    }

    virtual void onClick(float mouseX, float mouseY) {
        if (isClicked(mouseX, mouseY)) {
            handleClick();
        }
    }

protected:
    virtual void handleClick() {
        // Реалізуйте обробку кліку, якщо потрібно
    }
};

#endif // UIELEMENT_H
