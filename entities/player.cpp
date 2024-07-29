// player.cpp
#include "player.h"
#include <GL/glut.h>

Player::Player(float s, float r, float g, float b, int l, float speed) : size(s), lives(l), moveSpeed(speed) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Player::draw() {
    if (!visible) return;
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(-size / 2 + offsetX, -size / 2 + offsetY);
    glVertex2f(size / 2 + offsetX, -size / 2 + offsetY);
    glVertex2f(size / 2 + offsetX, size / 2 + offsetY);
    glVertex2f(-size / 2 + offsetX, size / 2 + offsetY);
    glEnd();
}

void Player::move(float dx, float dy) {
    offsetX += dx * moveSpeed;
    offsetY += dy * moveSpeed;
}
