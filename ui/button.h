#ifndef BUTTON_H
#define BUTTON_H

#include "uielement.h"

class Button : public UIElement {
public:
    std::function<void()> onClickCallback;

    Button(Align align, float offsetX, float offsetY, float rectX, float rectY, float rectWidth, float rectHeight, std::function<void()> onClickCallback)
        : UIElement(align, offsetX, offsetY, rectX, rectY, rectWidth, rectHeight), onClickCallback(onClickCallback) {}

    virtual void draw() override {
        UIElement::draw(); // Виклик базового методу для рендеринга кнопки
    }

protected:
    virtual void handleClick() override {
        if (onClickCallback) {
            onClickCallback(); // Виклик функції, переданої в конструктор
        }
    }
};

#endif // BUTTON_H
