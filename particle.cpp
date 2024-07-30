#include "particle.h"
#include <GL/glut.h>

Particle::Particle(float x, float y, float speedX, float speedY, float lifetime)
    : x(x), y(y), speedX(speedX), speedY(speedY), lifetime(lifetime) {}

void Particle::update(float deltaTime) {
    x += speedX * deltaTime;
    y += speedY * deltaTime;
    scale -= 0.02 * deltaTime;
    lifetime -= deltaTime;

}

void Particle::draw() const { // Метод константний
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x - scale, y - scale);
    glVertex2f(x + scale, y - scale);
    glVertex2f(x + scale, y + scale);
    glVertex2f(x - scale, y + scale);
    glEnd();
}

bool Particle::isAlive() const {
    return lifetime > 0.0f;
}
