#include "cue.hpp"
#include "measurements.hpp"
#include "display.hpp"
#include "colors.hpp"
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Cue::Cue(sf::Vector2f position, sf::Vector2f rotation) {
    this->position = position;
    this->rotation = rotation;
}

void Cue::getPosition(sf::RenderWindow &window) {
    // sf::Vector2i positionI = sf::Mouse::getPosition(window);
    // position = sf::Vector2f(positionI.x, positionI.y);
    position = sf::Vector2f(500, 200);
}

void Cue::getRotation(sf::RenderWindow &window) {
    sf::Vector2i positionI = sf::Mouse::getPosition(window);
    rotation = sf::Vector2f(positionI.x, positionI.y);
}

void Cue::Draw(sf::RenderWindow* window) {
    sf::Vector2f size = sf::Vector2f(CUE_LENGTH, CUE_TIP_WIDTH);
    size = positionToScreen(size) - positionToScreen(sf::Vector2f());
    sf::RectangleShape cueR = sf::RectangleShape(size);
    cueR.setPosition(position);
    cueR.setRotation(atan2(rotation.y - position.y, rotation.x - position.x) * 180 / M_PI);
    cueR.setFillColor(sf::Color::White);
    window->draw(cueR);
}