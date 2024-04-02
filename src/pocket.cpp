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

    // Get the ball's position
    sf::Vector2f ballPosition = ball.getPosition();

    // Get its radius
    float ballRadius = ball.getRadius();

    // Euclidian distance formula
    float distance = std::sqrt(std::pow(pocketPosition.x - ballPosition.x, 2) + std::pow(pocketPosition.y - ballPosition.y, 2));
    return distance <= (pocketRadius - ballRadius);
}
