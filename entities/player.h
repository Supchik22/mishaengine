// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "../canvasitem.h"

class Player : public CanvasItem {
public:
    float size;
    float color[3];
    int lives;
    float moveSpeed;
    Player(float s, float r, float g, float b, int l, float speed);
    virtual void update() override;
    virtual void draw() override;
    void move(float dx, float dy);
};

#endif // PLAYER_H
