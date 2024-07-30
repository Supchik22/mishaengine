#include "game.h"
#include <algorithm>

Game::Game()
    : mouseX(0.0f), mouseY(0.0f), player(nullptr),
      cameraX(0.0f), cameraY(0.0f), cameraZoom(0.0f) {
    for (int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

float Game::getMouseX() const {
    return mouseX;
}

void Game::setMouseX(float x) {
    mouseX = x;
}

float Game::getMouseY() const {
    return mouseY;
}

void Game::setMouseY(float y) {
    mouseY = y;
}

std::vector<CanvasItem*>& Game::getCanvasItems() {
    return canvasItems;
}


void Game::addCanvasItem(CanvasItem* item) {
    canvasItems.push_back(item);
}
void Game::removeCanvasItem(CanvasItem* item) {

    auto it = std::find(canvasItems.begin(), canvasItems.end(), item);
    if (it != canvasItems.end()) {

        canvasItems.erase(it); // Видалення з вектора
    }
}


Player* Game::getPlayer() const {
    return player;
}

void Game::setPlayer(Player* p) {
    player = p;
}

const std::vector<Enemy*>& Game::getEnemies() const {
    return enemies;
}

std::vector<Enemy*>& Game::getEnemies() {
    return enemies;
}

void Game::addEnemy(Enemy* enemy) {
    enemies.push_back(enemy);
}

const std::vector<Bullet*>& Game::getBullets() const {
    return bullets;
}

std::vector<Bullet*>& Game::getBullets() {
    return bullets;
}

void Game::addBullet(Bullet* bullet) {
    bullets.push_back(bullet);
}

float Game::getCameraX() const {
    return cameraX;
}

void Game::setCameraX(float x) {
    cameraX = x;
}

float Game::getCameraY() const {
    return cameraY;
}

void Game::setCameraY(float y) {
    cameraY = y;
}

float Game::getCameraZoom() const {
    return cameraZoom;
}

void Game::setCameraZoom(float zoom) {
    cameraZoom = zoom;
}

bool Game::getKey(int index) const {
    if (index >= 0 && index < 256) {
        return keys[index];
    }
    return false;
}

void Game::setKey(int index, bool value) {
    if (index >= 0 && index < 256) {
        keys[index] = value;
    }
}
