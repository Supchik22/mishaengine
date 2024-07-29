#include "sprite.h"
#include <SOIL/SOIL.h>
#include <iostream>

Sprite::Sprite(const std::string& imagePath, float width, float height) : width(width), height(height) {
    textureID = loadSOILTexture(imagePath);
}

Sprite::~Sprite() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
}

bool Sprite::loadTexture(const std::string& imagePath) {
    if (textureID) {
        glDeleteTextures(1, &textureID);
    }
    textureID = loadSOILTexture(imagePath);
    return textureID != 0;
}

GLuint Sprite::loadSOILTexture(const std::string& imagePath) {
    GLuint texture = SOIL_load_OGL_texture(
        imagePath.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (!texture) {
        std::cerr << "SOIL loading error: " << SOIL_last_result() << " for image " << imagePath << std::endl;
    }
    return texture;
}

void Sprite::draw() {

    if (!visible || !textureID) return;

    if (owner) {
        offsetX = owner->offsetX;
        offsetY = owner->offsetY;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(offsetX - width / 2, offsetY - height / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(offsetX + width / 2, offsetY - height / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(offsetX + width / 2, offsetY + height / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(offsetX - width / 2, offsetY + height / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
