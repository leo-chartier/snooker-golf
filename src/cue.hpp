#ifndef GAME_CUE
#define GAME_CUE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Cue {
    public:
        sf::Vector2f position;
        sf::Vector2f rotation;
        sf::Vector2i start;
        sf::Vector2i end;
        float power;
        float angle;
        bool check;
        bool startSet;

        Cue(sf::Vector2f position, sf::Vector2f rotation, float power, float angle);
        void getPosition(sf::RenderWindow &window);
        void getRotation(sf::RenderWindow &window);
        void Draw(sf::RenderWindow* window);
        void setPower(sf::RenderWindow &window);
};

#endif