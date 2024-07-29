
#include "bullet.h"
#include <GL/glut.h>
#include <cmath>

Bullet::Bullet(float x, float y, float tx, float ty, float s) : speed(s), targetX(tx), targetY(ty) {
    offsetX = x;
    offsetY = y;
}

void Bullet::update() {
    float dx = targetX - offsetX;
    float dy = targetY - offsetY;
    float length = std::sqrt(dx * dx + dy * dy);
    if (length > 0.01f) {
        dx /= length;
        dy /= length;
        move(dx * speed, dy * speed);
    } else {

    }
}

void Bullet::draw() {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.02f + offsetX, -0.02f + offsetY);
    glVertex2f(0.02f + offsetX, -0.02f + offsetY);
    glVertex2f(0.02f + offsetX, 0.02f + offsetY);
    glVertex2f(-0.02f + offsetX, 0.02f + offsetY);
    glEnd();
}
