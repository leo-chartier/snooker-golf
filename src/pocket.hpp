

#ifndef GAME_POCKET
#define GAME_POCKET

#include "measurements.hpp"
#include <SFML/Graphics.hpp>

class Pocket {
    public:
        Pocket(sf::Vector2f position, float radius);
        ~Pocket(void);
        void Draw(sf::RenderWindow* window);

    private:
        // A pocket is defined by it's radius and its position
        sf::Vector2f pocketPosition;
        float pocketRadius;

};

#endif