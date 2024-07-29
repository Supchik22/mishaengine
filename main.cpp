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


// Global variables
float mouseX = 0., mouseY = 0.;
std::vector<CanvasItem*> canvasItems;
Player* player;
std::vector<Enemy*> enemies;
std::vector<Bullet*> bullets;

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZoom = 0.0f;

bool keys[256];

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
    std::string livesText = "Lives: " + std::to_string(player->lives);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f+cameraX, 0.9f+cameraY);
    for (char c : livesText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void detectCollisions() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        Bullet* bullet = *it;
        bool bulletRemoved = false;

        for (auto jt = enemies.begin(); jt != enemies.end(); ) {
            Enemy* enemy = *jt;
            float dx = bullet->offsetX - enemy->offsetX;
            float dy = bullet->offsetY - enemy->offsetY;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < 0.1f) {

                delete enemy;

                jt = enemies.erase(jt);
                bulletRemoved = true;

                spawnEnemy();
                break;
            } else {
                ++jt;
            }
        }

        if (bulletRemoved) {
            delete bullet;
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void update() {
    if (keys['w']) {
        player->move(0.0f, 1.0f);
    }
    if (keys['s']) {
        player->move(0.0f, -1.0f);
    }
    if (keys['a']) {
        player->move(-1.0f, 0.0f);
    }
    if (keys['d']) {
        player->move(1.0f, 0.0f);
    }

    // Zoom
    if (keys['z']) {
        cameraZoom -= 0.01;
    }
    if (keys['x']) {
        cameraZoom += 0.01;
    }

    for (Enemy* enemy : enemies) {
        enemy->update();
    }
    for (Bullet* bullet : bullets) {
        bullet->update();
    }

    detectCollisions();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    cameraX = lerp(cameraX, player->offsetX, 0.1f);  // Smooth camera movement using lerp
    cameraY = lerp(cameraY, player->offsetY, 0.1f);  // Smooth camera movement using lerp
    glTranslatef(0.0 - cameraX, 0.0 - cameraY, cameraZoom);

    for (CanvasItem* item : canvasItems) {
        item->draw();
    }

    player->draw();
    for (Enemy* enemy : enemies) {
        enemy->draw();
    }
    for (Bullet* bullet : bullets) {
        bullet->draw();
    }

    displayLives();

    glutSwapBuffers();
}

void spawnEnemy() {



    Enemy* temp_enemy;
    temp_enemy = new Enemy(0.2f, 1.0f, 1.0f, 0.0f, player, 0.001f);
    temp_enemy->setPosition(randRangeF(-1.0f,2.0),randRangeF(-1.0f,2.0));

    enemies.push_back(temp_enemy);

}

void timer(int value) {
    update();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            cameraY -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            cameraY += 0.1f;
            break;
        case GLUT_KEY_LEFT:
            cameraX += 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            cameraX -= 0.1f;
            break;
    }
    glutPostRedisplay();
}

void initShapes() {
    Sprite* sprite = new Sprite("assets/cat.png", 0.2f, 0.2);

    canvasItems.push_back(sprite);

    canvasItems.push_back(player);
    sprite->owner = player;
    player->hide();
}

void mouse(int x, int y) {
    // Отримання розмірів вікна
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Перетворення координат миші на координати системи вікна
    float lMouseX = (float)x / windowWidth * 2.0f - 1.0f;
    float lMouseY = 1.0f - (float)y / windowHeight * 2.0f;

    // Врахування позиції камери
    mouseX = lMouseX + cameraX;
    mouseY = lMouseY + cameraY;
}

void initEnemies() {
    spawnEnemy();
}


void mouseEvent(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        bullets.push_back(new Bullet(player->offsetX, player->offsetY + 0.1f, mouseX, mouseY, 0.02f));
        AudioServer& audio = AudioServer::getInstance();
        audio.playSound("assets/shoot.ogg");
    }
}

int main(int argc, char** argv) {

    AudioServer& audio = AudioServer::getInstance();
    audio.playSound("assets/tickTock.ogg");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Dark magic");

    player = new Player(0.2f, 0.0f, 1.0f, 0.0f, 3, 0.01f);

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

    for (CanvasItem* item : canvasItems) {
        delete item;
    }
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    delete player;

    return 0;
}
