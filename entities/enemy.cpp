
#include "enemy.h"
#include <GL/glut.h>
#include <cmath>



Enemy::Enemy(float s, float r, float g, float b, Player* t, float speed) : size(s), target(t), moveSpeed(speed) {

    color[0] = r;
    color[1] = g;
    color[2] = b;
}

Enemy::~Enemy() {



}

void Enemy::draw() {
    if (!visible) return;
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(-size / 2 + offsetX, -size / 2 + offsetY);
    glVertex2f(size / 2 + offsetX, -size / 2 + offsetY);
    glVertex2f(size / 2 + offsetX, size / 2 + offsetY);
    glVertex2f(-size / 2 + offsetX, size / 2 + offsetY);
    glEnd();
}

void Enemy::update() {
    float dx = target->offsetX - offsetX;
    float dy = target->offsetY - offsetY;
    float length = std::sqrt(dx * dx + dy * dy);
    if (length > 0.1f) {
        dx /= length;
        dy /= length;
        move(dx * moveSpeed, dy * moveSpeed);
    }
}

void Enemy::setPosition(float x,float y) {
    offsetX = x;
    offsetY = y;

}
