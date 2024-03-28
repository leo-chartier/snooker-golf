#include "balls.cpp"
#include "display.cpp"
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "table.cpp"

using namespace std;
using namespace sf;

int main()
{
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE, Style::Close);

    Vector2f shape[] = {
        Vector2f(),
        Vector2f(CLASSIC_WIDTH, 0),
        Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT),
        Vector2f(0, CLASSIC_HEIGHT),
    };
    Table table = Table(shape, 4);

    CueBall cueBall = CueBall(Vector2f(SCREEN_W / 3, ((SCREEN_H - CLASSIC_HEIGHT) / 2 + (CLASSIC_WIDTH / 2))), BALL_RADIUS, CUE_BALL_COLOR);
    Ball ball = Ball(Vector2f((2 * CLASSIC_WIDTH) / 3, CLASSIC_HEIGHT / 2), BALL_RADIUS, BALL_COLOR);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Processing here

        drawGame(&window, &ball, &cueBall, &table);
    }

    return 0;
}