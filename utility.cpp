#include "utility.h"
#include <random>

float randRangeF(float min, float max) {
    std::random_device rd;

    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

int randRangeI(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
float lerp(float start, float end, float t) {
    return start + t * (end - start);
}
