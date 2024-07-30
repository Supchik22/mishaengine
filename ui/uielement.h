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

class UIElement : public CanvasItem {
public:
    Align align;  // Вирівнювання
    bool isHud;
    float offsetX, offsetY; // Зсуви
    float rectX, rectY, rectWidth, rectHeight; // Розмір та позиція елемента

    UIElement(Align align, float offsetX, float offsetY, float rectX, float rectY, float rectWidth, float rectHeight)
        : align(align), offsetX(offsetX), offsetY(offsetY), rectX(rectX), rectY(rectY), rectWidth(rectWidth), rectHeight(rectHeight), isHud(true)
    {}

    virtual ~UIElement() {}

    virtual void update() override {
        // Реалізуйте оновлення UI елемента
    }

    virtual void draw() override {
        if (visible) {
            float x = rectX;
            float y = rectY;

            if (isHud) {
                Game& game = Game::getInstance();
                x += game.getCameraX() + offsetX;
                y += game.getCameraY() + offsetY;
            } else {
                x += offsetX;
                y += offsetY;
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

            // Малюємо прямокутник як простий квадрат
            glColor3f(1.0f, 0.0f, 0.0f); // Червоний колір для видимості
            glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + rectWidth, y);
                glVertex2f(x + rectWidth, y + rectHeight);
                glVertex2f(x, y + rectHeight);
            glEnd();
        }
    }

    bool isClicked(float mouseX, float mouseY) const {
        float x = rectX + offsetX;
        float y = rectY + offsetY;

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
