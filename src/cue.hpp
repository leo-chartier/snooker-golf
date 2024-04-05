#ifndef GAME_CUE
#define GAME_CUE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const float BASE_POWER = 20.0f;

class Cue {
    public:
        sf::Vector2f position;
        sf::Vector2f direction;
        sf::Vector2f start;
        bool dragging;

        Cue(sf::Vector2f cueBallPos);
        void Draw(sf::RenderWindow* window, CueBall &cueBall, std::vector<Ball> &ballsList);
        void setPower(sf::RenderWindow &window, CueBall *cueBall, std::vector<Ball> &ballsList);
};

#endif