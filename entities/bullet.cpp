#include "bullet.h"

#include "enemy.h" // Уключіть заголовок Enemy
#include <GL/glut.h>
#include <cmath>



Bullet::Bullet(float x, float y, float tx, float ty, float s)
    : speed(s), targetX(tx), targetY(ty) {
    offsetX = x;
    offsetY = y;
}

void Bullet::update() {
    float dx = targetX - offsetX;
    float dy = targetY - offsetY;
    float length = std::sqrt(dx * dx + dy * dy);

    // Оновлення позиції кулі
    if (length > 0.01f) {
        dx /= length;
        dy /= length;
        move(dx * speed, dy * speed);
    } else {
        ParticleSystem::getInstance().addParticle(offsetX, offsetY, randRangeF(-0.1f,0.1f), randRangeF(-0.1f,0.1f), 1.0f);
        ParticleSystem::getInstance().addParticle(offsetX, offsetY, randRangeF(-0.1f,0.1f), randRangeF(-0.1f,0.1f), 1.0f);
        free();
    }

    // Перевірка на колізії з іншими об'єктами
    Game& game = Game::getInstance();
    auto& canvasItems = game.getCanvasItems();

    for (auto it = canvasItems.begin(); it != canvasItems.end(); ) {
        if (auto* enemy = dynamic_cast<Enemy*>(*it)) {
            float dx = offsetX - enemy->offsetX;
            float dy = offsetY - enemy->offsetY;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < 0.1f) { // Перевірка колізії
                enemy->free();

                free();
                //game.spawnEnemy(); // Спавн нового ворога
                return; // Переривання після колізії
            } else {
                ++it; // Переходимо до наступного елемента
            }
        } else {
            ++it; // Переходимо до наступного елемента
        }
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
