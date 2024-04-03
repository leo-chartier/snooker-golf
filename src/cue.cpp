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

void Cue::Draw(sf::RenderWindow* window, CueBall &cueBall, std::vector<Ball> &ballsList) {
    if (cueBall.Velocity.x != 0 || cueBall.Velocity.y != 0) {
        return;
    }
    for (int i = 0; i < ballsList.size(); i++) {
        if (ballsList[i].Velocity.x != 0 || ballsList[i].Velocity.y != 0) {
            return;
        }
    }
    if (!check){
        position = cueBall.Position;
    }
    sf::Vector2f size = sf::Vector2f(CUE_LENGTH, CUE_TIP_WIDTH);
    sf::RectangleShape cueR = sf::RectangleShape(size);
    cueR.setFillColor(sf::Color::White);

    cueR.setOrigin( - 2*BALL_RADIUS, CUE_TIP_WIDTH/2);
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

void Cue::setPower(sf::RenderWindow &window, CueBall *cueBall, std::vector<Ball> &ballsList) {
    if (cueBall->Velocity.x != 0 || cueBall->Velocity.y != 0) {
        return;
    }
    for (int i = 0; i < ballsList.size(); i++) {
        if (ballsList[i].Velocity.x != 0 || ballsList[i].Velocity.y != 0) {
            return;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!startSet){
            start = sf::Mouse::getPosition(window);
            check = true;
            startSet = true;
        }
        
        sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
        sf::Vector2f scaledMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f scaledStart = (sf::Vector2f)window.mapPixelToCoords(start);
        position = sf::Vector2f(cueBall->Position.x + scaledMouse.x - scaledStart.x, cueBall->Position.y + scaledMouse.y - scaledStart.y);
    }
    else if (check) {
        end = sf::Mouse::getPosition(window);
        check = false;
        startSet = false;
        power = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)) * CUE_BALL_RESTITUTION_COEFFICIENT;
        position = cueBall->Position;
        cueBall->Velocity = sf::Vector2f(-power * cos(angle * M_PI / 180), -power * sin(angle * M_PI / 180));
    }
}