#include "particles.h"
#include "particle.h"
#include <algorithm>

ParticleSystem& ParticleSystem::getInstance() {
    static ParticleSystem instance;
    return instance;
}

void ParticleSystem::addParticle(float x, float y, float speedX, float speedY, float lifetime) {
    particles.emplace_back(x, y, speedX, speedY, lifetime);
}

void ParticleSystem::update(float deltaTime) {
    for (auto& particle : particles) {
        particle.update(deltaTime);
    }

    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
                       [](const Particle& p) { return !p.isAlive(); }),
        particles.end());
}

void ParticleSystem::draw() const { // Метод константний
    for (const auto& particle : particles) {
        particle.draw();
    }
}
