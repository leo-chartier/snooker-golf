#ifndef GAME_TABLE
#define GAME_TABLE

#include "measurements.hpp"
#include <SFML/Graphics.hpp>

class Table {

    public:
        sf::ConvexShape* triangles;
        size_t nTriangles;
        // Pocket pocketArray[];
        float frictionCoefficient = BALL_FRICTION_COEFFICIENT;

        Table(sf::Vector2f shape[], size_t length);
        ~Table(void);
        void Draw(sf::RenderWindow* window);
};

#endif