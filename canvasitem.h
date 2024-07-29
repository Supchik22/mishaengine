#ifndef CANVASITEM_H
#define CANVASITEM_H

class CanvasItem {
public:
    float offsetX, offsetY;
    bool visible;

    CanvasItem() : offsetX(0.0f), offsetY(0.0f), visible(true) {}
    virtual ~CanvasItem() {}

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
};

#endif // CANVASITEM_H
