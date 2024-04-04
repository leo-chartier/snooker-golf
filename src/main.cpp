#include "balls.cpp"
#include "display.cpp"
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "table.cpp"
#include "cue.cpp"
#include "pocket.cpp"

using namespace std;
using namespace sf;

#include <time.h>
int main()
{
    srand(time(NULL)); // TEMP
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE, Style::Close);
    VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    Vector2f vertices[] = {
        Vector2f(  0,    144),
        Vector2f(192,    144),
        Vector2f(192,     88.58),
        Vector2f(182.06,  81.94),
        Vector2f(171.65,  66.37),
        Vector2f(168,     48),
        Vector2f(171.65,  29.63),
        Vector2f(182.06,  14.06),
        Vector2f(197.63,   3.65),
        Vector2f(216,      0),
        Vector2f(234.37,   3.65),
        Vector2f(249.94,  14.06),
        Vector2f(260.35,  29.63),
        Vector2f(264,     48),
        Vector2f(260.35,  66.37),
        Vector2f(249.94,  81.94),
        Vector2f(240,     88.58),
        Vector2f(240,    144),
        Vector2f(264,    144),
        Vector2f(291.55, 149.48),
        Vector2f(314.91, 165.09),
        Vector2f(330.52, 188.45),
        Vector2f(336,    216),
        Vector2f(330.52, 243.56),
        Vector2f(314.91, 266.91),
        Vector2f(291.55, 282.52),
        Vector2f(264,    288),
        Vector2f(236.44, 282.52),
        Vector2f(213.09, 266.91),
        Vector2f(197.48, 243.56),
        Vector2f(192,    216),
        Vector2f(192,    192),
        Vector2f(  0,    192),
    };
    size_t nVertices = sizeof(vertices) / sizeof(Vector2f);
    Table table = Table(vertices, nVertices);
    initializeWindowPosition(&window, table);

    // The list of pockets
    std::vector<Pocket> pocketList = {
        Pocket(Vector2f(216, 48), 2), // TEMP : Set the hole radius to 2 for now but should be tied to mouth size
    };

    CueBall cueBall = CueBall(Vector2f(24, 168), BALL_RADIUS, CUE_BALL_COLOR);

    double x0 = cueBall.Position.x + 48.0;
    double y0 = cueBall.Position.y;
    vector<Ball> ballsList;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j <= i; j++){
            double x = x0 + i * BALL_RADIUS * sqrt(3);
            double y = y0 + (j * 2 - i) * BALL_RADIUS;
            Ball ball = Ball(Vector2f(x, y), BALL_RADIUS, BALL_COLOR);
            ballsList.push_back(ball);
        }
    }

    Cue cue = Cue(cueBall.Position, Vector2f(0,0), 0, 0);

    sf::Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        // Check collision with each hole
        cue.setPower(window, &cueBall, ballsList);
        for (int i = 0; i < ballsList.size(); i++) {
            for (auto& pocket : pocketList) {

            // Check if ball came in contact with any of the pockets
                if (pocket.isBallInPocket(ballsList[i])) {
                    // std::cout << "The ball has fallen!" << "\n";
                    ballsList[i].setInactive();
                }

                // Check if cue ball (...)
                if (pocket.isBallInPocket(cueBall)) {
                    // std::cout << "The cue ball has fallen!" << "\n";
                    cueBall.setInactive();
                }
            }

            if (cueBall.IsActive()) {
                cueBall.Update(dt, ballsList);
            }

            if (ballsList[i].IsActive()) {
                ballsList[i].Update(dt, ballsList);
            }
        }
        cueBall.replace();


        // test(&window);
        drawGame(&window, ballsList, &cue,  &cueBall, &table, pocketList); // The number after pocketlist represents the number of pockets to draw
    }

    return 0;
}
