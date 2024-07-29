// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "../canvasitem.h"

class Bullet : public CanvasItem {
public:
    float speed;
    float targetX, targetY;
    Bullet(float x, float y, float tx, float ty, float s);
    void update();
    void draw() override;
};

#endif // BULLET_H
