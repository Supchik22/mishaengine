#ifndef SPRITE_H
#define SPRITE_H

#include "../canvasitem.h"
#include <string>
#include <GL/glut.h>

class Sprite : public CanvasItem {
public:
    GLuint textureID;
    float width, height;

    Sprite(const std::string& imagePath, float width, float height);
    ~Sprite();
    CanvasItem* owner;

    virtual void update() override;
    virtual void draw() override;

    bool loadTexture(const std::string& imagePath);


private:
    GLuint loadSOILTexture(const std::string& imagePath);
};

#endif // SPRITE_H
