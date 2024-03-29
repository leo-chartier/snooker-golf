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

float dotProduct(sf::Vector2f p1, sf::Vector2f p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

float crossProduct(sf::Vector2f p1, sf::Vector2f p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

sf::Vector2f project(sf::Vector2f point, sf::Vector2f p1, sf::Vector2f p2) {
    sf::Vector2f direction = p2 - p1;
    float lengthSquared = direction.x * direction.x + direction.y * direction.y;
    if (lengthSquared == 0)
        return p1;
    sf::Vector2f diff1 = point - p1;
    float dot = diff1.x * direction.x + diff1.y * direction.y;
    float t = std::clamp(dot / lengthSquared, 0.0f, 1.0f);
    return p1 + t * direction;
}