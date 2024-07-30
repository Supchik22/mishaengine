#include <GL/glut.h>
#include "canvasitem.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/bullet.h"
#include <vector>
#include <string>
#include <cmath>
#include "canvasitems/sprite.h"
#include <SOIL/SOIL.h>
#include "utility.h"
#include "audioserver.h"
#include "game.h"
#include "particles.h"


// Function declarations
void displayLives();
void detectCollisions();
void update();
void display();
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void initShapes();
void mouse(int x, int y);
void initEnemies();
void spawnEnemy();

void displayLives() {
    Game& game = Game::getInstance();
    Player* player = game.getPlayer();
    std::string livesText = "Lives: " + std::to_string(player->lives);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f + game.getCameraX(), 0.9f + game.getCameraY());
    for (char c : livesText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}



void update() {
    Game& game = Game::getInstance();
    Player* player = game.getPlayer();
    if (game.getKey('w')) {
        player->move(0.0f, 1.0f);
    }
    if (game.getKey('s')) {
        player->move(0.0f, -1.0f);
    }
    if (game.getKey('a')) {
        player->move(-1.0f, 0.0f);
    }
    if (game.getKey('d')) {
        player->move(1.0f, 0.0f);
    }

    // Zoom
    if (game.getKey('z')) {
        game.setCameraZoom(game.getCameraZoom() - 0.01f);
    }
    if (game.getKey('x')) {
        game.setCameraZoom(game.getCameraZoom() + 0.01f);
    }

    for (CanvasItem* item : game.getCanvasItems()) {
        item->update();
    }

    ParticleSystem& particleSystem = ParticleSystem::getInstance();
    particleSystem.update(0.016f);
}

void display() {
    Game& game = Game::getInstance();
    Player* player = game.getPlayer();

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    game.setCameraX(lerp(game.getCameraX(), player->offsetX, 0.1f));  // Smooth camera movement using lerp
    game.setCameraY(lerp(game.getCameraY(), player->offsetY, 0.1f));  // Smooth camera movement using lerp
    glTranslatef(0.0 - game.getCameraX(), 0.0 - game.getCameraY(), game.getCameraZoom());

    for (CanvasItem* item : game.getCanvasItems()) {
        item->draw();
    }

    displayLives();
    ParticleSystem& particleSystem = ParticleSystem::getInstance();


    particleSystem.draw();


    glutSwapBuffers();
}

void spawnEnemy() {
    Game& game = Game::getInstance();

    Enemy* temp_enemy = new Enemy(0.2f, 1.0f, 1.0f, 0.0f, game.getPlayer(), 0.001f);
    temp_enemy->setPosition(randRangeF(-1.0f, 2.0f), randRangeF(-1.0f, 2.0f));

    game.addCanvasItem(temp_enemy);
    game.addEnemy(temp_enemy);
}

void timer(int value) {
    update();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    Game::getInstance().setKey(key, true);
}

void keyboardUp(unsigned char key, int x, int y) {
    Game::getInstance().setKey(key, false);
}

void specialKeys(int key, int x, int y) {
    Game& game = Game::getInstance();
    switch (key) {
        case GLUT_KEY_UP:
            game.setCameraY(game.getCameraY() - 0.1f);
            break;
        case GLUT_KEY_DOWN:
            game.setCameraY(game.getCameraY() + 0.1f);
            break;
        case GLUT_KEY_LEFT:
            game.setCameraX(game.getCameraX() + 0.1f);
            break;
        case GLUT_KEY_RIGHT:
            game.setCameraX(game.getCameraX() - 0.1f);
            break;
    }
    glutPostRedisplay();
}

void initShapes() {
    Game& game = Game::getInstance();
    Player* player = game.getPlayer();

    Sprite* sprite = new Sprite("assets/cat.png", 0.2f, 0.2f);

    game.addCanvasItem(sprite);
    game.addCanvasItem(player);

    sprite->owner = player;
    player->hide();
}

void mouse(int x, int y) {
    Game& game = Game::getInstance();

    // Отримання розмірів вікна
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Перетворення координат миші на координати системи вікна
    float lMouseX = (float)x / windowWidth * 2.0f - 1.0f;
    float lMouseY = 1.0f - (float)y / windowHeight * 2.0f;

    // Врахування позиції камери
    game.setMouseX(lMouseX + game.getCameraX());
    game.setMouseY(lMouseY + game.getCameraY());
}

void initEnemies() {
    spawnEnemy();
}

void mouseEvent(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        Game& game = Game::getInstance();



        game.addCanvasItem(new Bullet(game.getPlayer()->offsetX, game.getPlayer()->offsetY + 0.1f, game.getMouseX(), game.getMouseY(), 0.02f));
        AudioServer& audio = AudioServer::getInstance();
        audio.playSound("assets/shoot.ogg");
    }
}

int main(int argc, char** argv) {
    Game& game = Game::getInstance();
    AudioServer& audio = AudioServer::getInstance();
    audio.playSound("assets/tickTock.ogg");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Dark magic");

    game.setPlayer(new Player(0.2f, 0.0f, 1.0f, 0.0f, 3, 0.01f));

    initShapes();
    initEnemies();
    glutPassiveMotionFunc(mouse);

    glutMouseFunc(mouseEvent);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);

    glutTimerFunc(16, timer, 0);

    glutMainLoop();

    for (CanvasItem* item : game.getCanvasItems()) {
        delete item;
    }
    for (Enemy* enemy : game.getEnemies()) {
        delete enemy;
    }
    for (Bullet* bullet : game.getBullets()) {
        delete bullet;
    }
    delete game.getPlayer();

    return 0;
}
