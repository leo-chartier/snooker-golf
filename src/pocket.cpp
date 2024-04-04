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
    circle.setOrigin(Vector2f(POCKET_RADIUS, POCKET_RADIUS));
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
    float distance = vectorLength(ball.Position - pocketPosition);
    return distance <= pocketRadius + BALL_RADIUS;
}
