#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    Particle(float x, float y, float speedX, float speedY, float lifetime);

    void update(float deltaTime);
    void draw() const;

    bool isAlive() const;

private:
    float x, y;
    float speedX, speedY;
    float lifetime;
    float age;
    float scale = 0.02f;
};

#endif // PARTICLE_H
