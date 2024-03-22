#ifndef GAME_CUE
#define GAME_CUE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "colors.hpp"

class Cue {
    public:
        sf::Vector2f position;
        sf::Vector2f rotation;
        float power;
        float angle;

        Cue(sf::Vector2f position, sf::Vector2f rotation);
        void getPosition(sf::RenderWindow &window);
        void getRotation(sf::RenderWindow &window);
        void Draw(sf::RenderWindow* window);
};

#endif