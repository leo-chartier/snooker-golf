#include "cue.hpp"
#include "measurements.hpp"
#include "display.hpp"
#include "colors.hpp"
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Cue::Cue(sf::Vector2f position, sf::Vector2f rotation, float power, float angle) {
    this->position = position;
    this->rotation = rotation;
    this->power = 0;
    this->angle = 0;
}

void Cue::getPosition(sf::RenderWindow &window) {
    // sf::Vector2i positionI = sf::Mouse::getPosition(window);
    // position = sf::Vector2f(positionI.x, positionI.y);
    // position = sf::Vector2f(500, 200);
}

void Cue::getRotation(sf::RenderWindow &window) {
    sf::Vector2i positionI = sf::Mouse::getPosition(window);
    rotation = sf::Vector2f(positionI.x, positionI.y);
}

void Cue::Draw(sf::RenderWindow* window) {
    this->getPosition(*window);
    this->getRotation(*window);
    sf::Vector2f size = sf::Vector2f(CUE_LENGTH, CUE_TIP_WIDTH);
    size = positionToScreen(size) - positionToScreen(sf::Vector2f());
    sf::RectangleShape cueR = sf::RectangleShape(size);
    cueR.setPosition(position);
    cueR.setRotation(atan2(rotation.y - position.y, rotation.x - position.x) * 180 / M_PI);
    cueR.setFillColor(sf::Color::White);
    window->draw(cueR);
}

void Cue::setPower(sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i trueStart = sf::Mouse::getPosition(window);
        start = sf::Mouse::getPosition(window);
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            end = sf::Mouse::getPosition(window);
            position = position + sf::Vector2f(end.x - start.x, end.y - start.y);
            start = end;
            drawGame(&window, NULL, this);
        }
        power = sqrt(pow(end.x - trueStart.x, 2) + pow(end.y - trueStart.y, 2));
    }
    position = sf::Vector2f(500, 200); // TODO: replace with whiteball position
}