#ifndef GAME_TABLE
#define GAME_TABLE

#include "measurements.hpp"
#include <SFML/Graphics.hpp>

class Table {

    public:
        std::vector<sf::Vector2f> points;
        size_t nPoints;
        sf::ConvexShape* triangles;
        size_t nTriangles;
        // Pocket pocketArray[];
        float frictionCoefficient = BALL_FRICTION_COEFFICIENT;

        Table(std::vector<sf::Vector2f> points);
        void Draw(sf::RenderWindow* window);
};

#endif