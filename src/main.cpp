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
    std::vector<Pocket> pocketList = {Pocket(Vector2f(12, 12), 2), // TEMP : Set the hole radius to 2 for now but should be tied to mouth size
                            Pocket(Vector2f(12, 8), 2),
                            Pocket(Vector2f(16, 8), 2),
                            Pocket(Vector2f(20, 8), 2),
                            Pocket(Vector2f(24, 8), 2),
                            Pocket(Vector2f(28, 8), 2),
                            Pocket(Vector2f(32, 8), 2),
                            Pocket(Vector2f(36, 8), 2),
                            Pocket(Vector2f(40, 8), 2),
                            Pocket(Vector2f(44, 8), 2),
                            Pocket(Vector2f(48, 8), 2),
                            Pocket(Vector2f(52, 8), 2),
                            Pocket(Vector2f(56, 8), 2),
                            Pocket(Vector2f(60, 8), 2),
                            Pocket(Vector2f(64, 8), 2),
                            Pocket(Vector2f(68, 8), 2),
                            Pocket(Vector2f(72, 8), 2),
                            Pocket(Vector2f(76, 8), 2),
                            Pocket(Vector2f(80, 8), 2),
                            Pocket(Vector2f(80, 12), 2),
                            Pocket(Vector2f(80, 16), 2),
                            Pocket(Vector2f(80, 20), 2),
                            Pocket(Vector2f(80, 24), 2),
                            Pocket(Vector2f(80, 28), 2),
                            Pocket(Vector2f(80, 32), 2),
                            Pocket(Vector2f(80, 36), 2),
                            Pocket(Vector2f(76, 36), 2),
                            Pocket(Vector2f(72, 36), 2),
                            Pocket(Vector2f(68, 36), 2),
                            Pocket(Vector2f(64, 36), 2),
                            Pocket(Vector2f(60, 36), 2),
                            Pocket(Vector2f(56, 36), 2),
                            Pocket(Vector2f(52, 36), 2),
                            Pocket(Vector2f(48, 36), 2),
                            Pocket(Vector2f(44, 36), 2),
                            Pocket(Vector2f(40, 36), 2),
                            Pocket(Vector2f(36, 36), 2),
                            Pocket(Vector2f(32, 36), 2),
                            Pocket(Vector2f(28, 36), 2),
                            Pocket(Vector2f(24, 36), 2),
                            Pocket(Vector2f(20, 36), 2),
                            Pocket(Vector2f(16, 36), 2),
                            Pocket(Vector2f(12, 36), 2),
                            Pocket(Vector2f(12, 32), 2),
                            Pocket(Vector2f(12, 28), 2),
                            Pocket(Vector2f(12, 24), 2),
                            Pocket(Vector2f(12, 20), 2),
                            Pocket(Vector2f(12, 16), 2),
                            Pocket(Vector2f(12, 12), 2),
                            };

    CueBall cueBall = CueBall(Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2), BALL_RADIUS, CUE_BALL_COLOR);
    Ball ball = Ball(Vector2f(CLASSIC_WIDTH * 3 / 4, CLASSIC_HEIGHT * 0.51), BALL_RADIUS, BALL_COLOR);

    sf::Clock clock;

    // TEMP
    cueBall.Velocity.x = 115.0f;

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

        // Check collision with each hole
        for (auto& pocket : pocketList) {

            // Check if ball came in contact with any of the pockets
            if (pocket.isBallInPocket(ball)) {
                std::cout << "The ball has fallen!" << "\n";
            }
            
            // Check if cue ball (...)
            if (pocket.isBallInPocket(cueBall)) {
                std::cout << "The cue ball has fallen!" << "\n";
            }
        }

        // test(&window);
        drawGame(&window, &ball, &cueBall, &table, pocketList, 50); // The number after pocketlist represents the number of pockets to draw
    }

    return 0;
}

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
