#include <GL/glew.h>
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
#include "ui/button.h"

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
void reshape(int width, int height);

int windowWidth = 800;
int windowHeight = 600;

void displayLives() {
    Game& game = Game::getInstance();
    Player* player = game.getPlayer();
    std::string livesText = "Lives: " + std::to_string(player->lives);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Отримання розмірів вікна
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float aspectRatio = (float)windowWidth / (float)windowHeight;

    float xPosition = -0.9f * (windowWidth >= windowHeight ? aspectRatio : 1.0f) + game.getCameraX();
    float yPosition = 0.9f * (windowWidth < windowHeight ? aspectRatio : 1.0f) + game.getCameraY();

    glRasterPos2f(xPosition, yPosition);

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
void reshape(int width, int height) {
    // Зберігаємо нові розміри вікна
    windowWidth = width;
    windowHeight = height;

    // Встановлюємо новий розмір вікна
    glViewport(0, 0, width, height);

    // Обчислюємо співвідношення сторін
    float aspectRatio = (float)width / (float)height;

    // Встановлюємо перспективну проекцію
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        // Якщо вікно ширше або таке ж як і високе
        gluOrtho2D(-aspectRatio, aspectRatio, -1.0, 1.0);
    } else {
        // Якщо вікно вище ніж ширше
        gluOrtho2D(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

    sprite->owner = player;
    game.addCanvasItem(sprite);
    game.addCanvasItem(player);

    player->hide();
}

void mouse(int x, int y) {
    Game& game = Game::getInstance();



    // Перетворення координат миші на координати системи вікна
    float aspect_ratio = (float)windowWidth / (float)windowHeight;
    float lMouseX, lMouseY;

    if (windowWidth >= windowHeight) {
        lMouseX = ((float)x / windowWidth * 2.0f - 1.0f) * aspect_ratio;
        lMouseY = 1.0f - (float)y / windowHeight * 2.0f;
    } else {
        lMouseX = (float)x / windowWidth * 2.0f - 1.0f;
        lMouseY = (1.0f - (float)y / windowHeight * 2.0f) / aspect_ratio;
    }

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

        // Отримання розмірів вікна
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        // Перетворення координат миші на координати системи вікна
        float mouseX = (float)x / windowWidth * 2.0f - 1.0f;
        float mouseY = 1.0f - (float)y / windowHeight * 2.0f;

        for (CanvasItem* item : game.getCanvasItems()) {
            UIElement* uiElement = dynamic_cast<UIElement*>(item);
            if (uiElement) {
                uiElement->onClick(mouseX, mouseY);
            }

        }

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
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    game.setPlayer(new Player(0.2f, 0.0f, 1.0f, 0.0f, 3, 0.01f));
    // Отримання розмірів вікна
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    initShapes();
    initEnemies();
    glutPassiveMotionFunc(mouse);

    glutMouseFunc(mouseEvent);

    Button* button = new Button(
        Align::CENTER, ScreenPosition::TOP, 0.0f, 0.0f, -0.15f, -0.05f, 0.3f, 0.1f,
        []() {
            std::cout << "Hello World" << std::endl;
        }
    );


    game.addCanvasItem(button);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // Додайте цю лінію
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Колір фону
    glutTimerFunc(16, timer, 0);

    glutMainLoop();

    for (CanvasItem* item : game.getCanvasItems()) {
        delete item;
    }
    delete game.getPlayer();

    return 0;
}
