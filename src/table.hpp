#ifndef GAME_TABLE
#define GAME_TABLE

#include "measurements.hpp"
#include <SFML/Graphics.hpp>

class Table {

    public:
        sf::Vector2f* points;
        size_t nPoints;
        sf::ConvexShape* triangles;
        size_t nTriangles;
        // Pocket pocketArray[];
        float frictionCoefficient = BALL_FRICTION_COEFFICIENT;

        Table(sf::Vector2f points[], size_t length);
        void Draw(sf::RenderWindow* window);
};

#endif