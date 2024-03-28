#include <SFML/Graphics.hpp>

#include "utils.hpp"

#include <math.h>

float vectorLength(sf::Vector2f vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f normalize(sf::Vector2f vector) {
    float squaredNorm = vector.x * vector.x + vector.y * vector.y;
    if (squaredNorm == 0)
        return sf::Vector2f();
    // float inverseNorm  = squaredNorm;
    // long i  = * ( long * ) &inverseNorm;
    // i  = 0x5f3759df - ( i >> 1 );
    // inverseNorm  = * ( float * ) &i;
    // inverseNorm  = inverseNorm * ( 1.5f - ( squaredNorm * inverseNorm * inverseNorm / 2 ) );
    // return vector * inverseNorm;
    return vector / sqrt(squaredNorm);
}