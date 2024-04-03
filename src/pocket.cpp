#include "pocket.hpp"

#include "display.hpp"
#include "measurements.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

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

// Position Getter
sf::Vector2f Pocket::getPosition() {
    return pocketPosition;
}

// Radius Getter
float Pocket::getRadius() {
    return pocketRadius;
}

// Check if ball is in pocket
bool Pocket::isBallInPocket(const Ball& ball) {

    // Euclidian distance formula
    float distance = std::sqrt(std::pow(pocketPosition.x + pocketRadius/2 - ball.Position.x + BALL_RADIUS/2, 2) + std::pow(pocketPosition.y + pocketRadius/2 - ball.Position.y + BALL_RADIUS/2, 2));
    if (distance < pocketRadius/2 + BALL_RADIUS/2) {
        return true;
    }
    return false;
}
