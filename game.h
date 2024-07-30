#ifndef GAME_H
#define GAME_H

#include <vector>

class CanvasItem;
class Player;
class Enemy;
class Bullet;

class Game {
public:
    static Game& getInstance();

    // Getters and Setters for variables
    float getMouseX() const;
    void setMouseX(float x);

    float getMouseY() const;
    void setMouseY(float y);

    std::vector<CanvasItem*>& getCanvasItems();
    void addCanvasItem(CanvasItem* item);
    void removeCanvasItem(CanvasItem* item);

    Player* getPlayer() const;
    void setPlayer(Player* p);

    const std::vector<Enemy*>& getEnemies() const;
    std::vector<Enemy*>& getEnemies();
    void addEnemy(Enemy* enemy);

    const std::vector<Bullet*>& getBullets() const;
    std::vector<Bullet*>& getBullets();
    void addBullet(Bullet* bullet);

    float getCameraX() const;
    void setCameraX(float x);

    float getCameraY() const;
    void setCameraY(float y);

    float getCameraZoom() const;
    void setCameraZoom(float zoom);

    bool getKey(int index) const;
    void setKey(int index, bool value);

private:
    Game(); // Private constructor
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Member variables
    float mouseX, mouseY;
    std::vector<CanvasItem*> canvasItems;
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    float cameraX, cameraY, cameraZoom;
    bool keys[256];
};

#endif // GAME_H
