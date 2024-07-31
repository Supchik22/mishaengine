#ifndef BUTTON_H
#define BUTTON_H

#include "uielement.h"

class Button : public UIElement {
public:
    std::function<void()> onClickCallback;

    Button(Align align, ScreenPosition screenPosition, float offsetX, float offsetY, float rectX, float rectY, float rectWidth, float rectHeight, std::function<void()> onClickCallback)
        : UIElement(align, screenPosition, offsetX, offsetY, rectX, rectY, rectWidth, rectHeight), onClickCallback(onClickCallback) {}


    virtual void draw() override {
       if (visible) {
            Game& game = Game::getInstance();
            float x = rectX + offsetX;
            float y = rectY + offsetY;



            // Обчислення координат залежно від позиції на екрані
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
            if (isHud) {

                x += game.getCameraX();
                y += game.getCameraY();
            }
            // Обчислення координат залежно від вирівнювання
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

protected:
    virtual void handleClick() override {
        if (onClickCallback) {
            onClickCallback(); // Виклик функції, переданої в конструктор
        }
    }
};

#endif // BUTTON_H
