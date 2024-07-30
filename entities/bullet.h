// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "../canvasitem.h"
#include "../game.h"
#include "../particles.h"
#include "../utility.h"
class Bullet : public CanvasItem {
public:
    float speed;
    float targetX, targetY;
    Bullet(float x, float y, float tx, float ty, float s);
    virtual void update() override;
    virtual void draw() override;
};

#endif // BULLET_H
