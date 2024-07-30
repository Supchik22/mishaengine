#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include "particle.h"

class ParticleSystem {
public:
    static ParticleSystem& getInstance();
    void addParticle(float x, float y, float speedX, float speedY, float lifetime);
    void update(float deltaTime);
    void draw() const; // Метод константний

private:
    ParticleSystem() = default;
    std::vector<Particle> particles;
};

#endif // PARTICLES_H
