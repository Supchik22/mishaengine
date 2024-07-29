
#ifndef ENEMY_H
#define ENEMY_H

#include "../canvasitems/sprite.h"
#include "../canvasitem.h"
#include "player.h"

class Enemy : public CanvasItem {
public:
    float size;
    float color[3];

    Player* target;
    float moveSpeed;
    Enemy(float s, float r, float g, float b, Player* t, float speed);
    ~Enemy();
    void draw() override;
    void update();
    void setPosition(float x, float y);
};

#endif // ENEMY_H
