#include "cue.hpp"
#include "measurements.hpp"
#include "display.hpp"
#include "colors.hpp"
#include "balls.hpp"
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Load sound effects: cue hit
sf::SoundBuffer cueHitBuffer;
sf::Sound cueHitSound;

Cue::Cue(Vector2f cueBallPos) {
    this->start = cueBallPos;
    this->dragging = false;

    // Load the cue hit sound effect when the Cue object is created
    if (!cueHitBuffer.loadFromFile("assets/sounds/cueball.ogg")) {
        std::cerr << "Error loading cue hit sound effect" << std::endl;
        throw std::runtime_error("Failed to load cue hit sound effect");
    }

    cueHitSound.setBuffer(cueHitBuffer);
}

void Cue::Draw(sf::RenderWindow* window, CueBall &cueBall, std::vector<Ball> &ballsList) {
    if (cueBall.Velocity.x != 0 || cueBall.Velocity.y != 0) {
        return;
    }
    for (int i = 0; i < ballsList.size(); i++) {
        if (ballsList[i].Velocity.x != 0 || ballsList[i].Velocity.y != 0) {
            return;
        }
    }

    sf::Vector2f size = sf::Vector2f(CUE_LENGTH, CUE_TIP_WIDTH);
    sf::RectangleShape cueR = sf::RectangleShape(size);
    cueR.setFillColor(sf::Color::White);

    cueR.setOrigin(-2 * BALL_RADIUS, CUE_TIP_WIDTH / 2);
    cueR.setPosition(position.x, position.y);

    // Calculate the angle between the cue ball and the mouse position
    float angleCueR = atan2(direction.y, direction.x) * 180 / M_PI;
    // printf("%f %f %f\n", direction.x, direction.y, angleCueR);
    cueR.setRotation(angleCueR);

    window->draw(cueR);
}

void Cue::setPower(sf::RenderWindow &window, CueBall *cueBall, std::vector<Ball> &ballsList) {
    if (cueBall->Velocity.x != 0 || cueBall->Velocity.y != 0) {
        return;
    }
    for (int i = 0; i < ballsList.size(); i++) {
        if (ballsList[i].Velocity.x != 0 || ballsList[i].Velocity.y != 0) {
            return;
        }
    }

    // Pre-calculate values
    Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    this->direction = normalize(mousePos - start);
    float distance = vectorLength(mousePos - start);
    distance = std::min(distance, 20 * BALL_RADIUS);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Setting position
        if (!dragging){
            start = mousePos;
            dragging = true;
        }
        this->position = cueBall->Position + distance * direction;
    } else if (dragging) {
        // We just released the mouse, launch the ball
        cueHitSound.play();
        cueBall->Velocity = -direction * BASE_POWER * distance * CUE_BALL_RESTITUTION_COEFFICIENT;
        dragging = false;
    } else {
        // Freely moving around
        this->direction = normalize(mousePos - cueBall->Position);
        this->position = cueBall->Position;
    }
}