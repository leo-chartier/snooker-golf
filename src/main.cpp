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
    std::vector<Pocket> pocketList = {Pocket(Vector2f(0, 0), 2), // TEMP : Set the hole radius to 2 for now but should be tied to mouth size
                                    Pocket(Vector2f((CLASSIC_WIDTH / 2) - 2, 0), 2),
                                    Pocket(Vector2f(CLASSIC_WIDTH - 4, 0), 2),
                                    Pocket(Vector2f(0, CLASSIC_HEIGHT - 4), 2),
                                    Pocket(Vector2f((CLASSIC_WIDTH / 2) -2, CLASSIC_HEIGHT - 4), 2),
                                    Pocket(Vector2f(CLASSIC_WIDTH - 4, CLASSIC_HEIGHT -4), 2)
    };

    CueBall cueBall = CueBall(Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2), BALL_RADIUS, CUE_BALL_COLOR);

    vector<Ball> ballsList;
    for (int i = 0; i < 15; i++) {
        Ball ball = Ball(Vector2f(99, 99), BALL_RADIUS, BALL_COLOR);
        ballsList.push_back(ball);
    }

    // Set the position of the balls
    for (int i = 0; i < 5; i++){
        for (int j = 0; j <= i; j++){
            double x = CLASSIC_WIDTH * 3 / 4 + i * BALL_RADIUS*2 * cos(M_PI/6);
            double y = CLASSIC_HEIGHT / 2 + j * BALL_RADIUS*2 * sin(M_PI/6);
            ballsList[i * (i + 1) / 2 + j].Position = Vector2f(x, y);
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
        drawGame(&window, ballsList, &cue,  &cueBall, &table, pocketList, 6); // The number after pocketlist represents the number of pockets to draw
    }

    return 0;
}
