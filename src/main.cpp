#include "balls.cpp"
#include "display.cpp"
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "table.cpp"
#include "pocket.cpp"

using namespace std;
using namespace sf;

int main()
{
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE, Style::Close);
    VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));
    initializeWindowPosition(&window);

    Vector2f shape[] = {
        Vector2f(),
        Vector2f(CLASSIC_WIDTH, 0),
        Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT),
        Vector2f(0, CLASSIC_HEIGHT),
    };


    Table table = Table(shape, 4);

    // The list of pockets
    std::vector<Pocket> pocketList = {Pocket(Vector2f(-4, -4), CLASSIC_SIDE_MOUTH/2.5),
                            Pocket(Vector2f(96, -4), CLASSIC_SIDE_MOUTH/2.5),
                            Pocket(Vector2f(96, 48), CLASSIC_SIDE_MOUTH/2.5),
                            // Pocket(Vector2f(96, 48), CLASSIC_SIDE_MOUTH/2.5),
                            // Pocket(Vector2f(0, 0), CLASSIC_SIDE_MOUTH/2.5),
                            Pocket(Vector2f(-4, 48), CLASSIC_SIDE_MOUTH/2.5)};

    CueBall cueBall = CueBall(Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2), BALL_RADIUS, CUE_BALL_COLOR);
    Ball ball = Ball(Vector2f(CLASSIC_WIDTH * 3 / 4, CLASSIC_HEIGHT * 0.51), BALL_RADIUS, BALL_COLOR);

    sf::Clock clock;

    // TEMP
    cueBall.Velocity.x = 150.0f;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Processing here
        float dt = clock.restart().asSeconds();
        cueBall.Update(dt, &ball);
        ball.Update(dt, &cueBall);

        // test(&window);
        drawGame(&window, &ball, &cueBall, &table, pocketList, 4);
    }

    return 0;
}
/*
void test(RenderWindow* window) {
    window->clear();

    Vector2f p1 = Vector2f(CLASSIC_WIDTH * 0.2, 0);
    Vector2f p2 = Vector2f(CLASSIC_WIDTH * 0.8, CLASSIC_HEIGHT * 0.5);
    Vector2f p3 = Vector2f(CLASSIC_WIDTH * 0.6, CLASSIC_HEIGHT * 0.7);
    Vector2f v1 = normalize(p2 - p1) * 10.0f;
    Vector2f v2 = Vector2f(0, 0);
    float r = 10;
    Vector2 offset(r, r);

    Vector2f projection = project(p3, p1, p2);
    float distance = vectorLength(p3 - projection);
    Vector2f direction = normalize(p2 - p1);
    float distanceToProjection = sqrt(4 * r * r - distance * distance);
    Vector2f hit = projection - direction * distanceToProjection;
    Vector2f relativePosition = p3 - hit;
    Vector2f relativeVelocity = v2 - v1;
    float dotProduct = relativeVelocity.x * relativePosition.x + relativeVelocity.y * relativePosition.y;
    float factor = dotProduct / (distance * distance);
    Vector2f v1_ = v1 + factor * relativePosition;
    Vector2f v2_ = v2 - factor * relativePosition;
    float remainingFactor = vectorLength(p2 - p1) / vectorLength(p2 - hit);
    Vector2f p2_ = hit + v1_ * remainingFactor;
    Vector2f p3_ = p3 + v2_ * remainingFactor;

    CircleShape end_(r);
    end_.setPosition(p2_ - offset);
    end_.setFillColor(Color::Cyan);
    window->draw(end_);
    CircleShape other_(r);
    other_.setPosition(p3_ - offset);
    other_.setFillColor(Color::Magenta);
    window->draw(other_);
    CircleShape start(r);
    start.setPosition(p1 - offset);
    start.setFillColor(Color::White);
    window->draw(start);
    CircleShape end(r);
    end.setPosition(p2 - offset);
    end.setFillColor(Color::White);
    window->draw(end);
    CircleShape other(r);
    other.setPosition(p3 - offset);
    other.setFillColor(Color::Red);
    window->draw(other);
    CircleShape hitBall(r);
    hitBall.setPosition(hit - offset);
    hitBall.setFillColor(Color::Blue);
    window->draw(hitBall);

    drawLine(window, p1, p2, Color::Green);
    // drawLine(window, p3, projection, Color::White);
    drawLine(window, hit, hit + v1_, Color::White);
    drawLine(window, p3, p3 + v2_, Color::White);
    window->display();
}
*/