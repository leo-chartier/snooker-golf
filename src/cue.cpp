#include "cue.hpp"
#include "measurements.hpp"
#include "display.hpp"
#include "colors.hpp"
#include "balls.hpp"
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Cue::Cue(sf::Vector2f position, sf::Vector2f rotation, float power, float angle) {
    this->position = position;
    this->rotation = rotation;
    this->power = 0;
    this->angle = 0;
    this->check = false;
    this->startSet = false;
}

void Cue::Draw(sf::RenderWindow* window, CueBall &cueBall) {
    sf::Vector2f size = sf::Vector2f(CUE_LENGTH, CUE_TIP_WIDTH);
    sf::RectangleShape cueR = sf::RectangleShape(size);
    cueR.setFillColor(sf::Color::White);

    cueR.setPosition(position.x, position.y);

    // Scale the coordinates of the mouse to the view of the window
    sf::Vector2f scaledMouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    // Calculate the difference between the scaled mouse position and the cue ball position
    float dx = scaledMouse.x - cueBall.Position.x;
    float dy = scaledMouse.y - cueBall.Position.y;

    // Calculate the angle between the cue ball and the mouse position
    float angleCueR = atan2(dy, dx);
    angleCueR = angleCueR * 180 / M_PI;
    cueR.setRotation(angleCueR);
    angle = angleCueR;

    window->draw(cueR);
}

void Cue::setPower(sf::RenderWindow &window, CueBall *cueBall) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!startSet){
            start = sf::Mouse::getPosition(window);
            check = true;
            startSet = true;
        }
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        position = sf::Vector2f(cueBall->Position.x + mouse.x - start.x, cueBall->Position.y + mouse.y - start.y);
    }
    else if (check) {
        end = sf::Mouse::getPosition(window);
        check = false;
        startSet = false;
        power = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
        std::cout << "Power: " << power << std::endl;
        position = cueBall->Position;
    }
}