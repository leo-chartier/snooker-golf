#include "pocket.hpp"

#include "display.hpp"
#include "measurements.hpp"
#include <SFML/Graphics.hpp>

// Constructor
Pocket::Pocket(sf::Vector2f position, float radius) : pocketPosition(position), pocketRadius(radius) {}

// Destructor
Pocket::~Pocket() {}

// Draw function
void Pocket::Draw(sf::RenderWindow* window) {
    sf::CircleShape circle(pocketRadius);
    circle.setPosition(pocketPosition);
    circle.setFillColor(sf::Color::Black);
    window->draw(circle);
}