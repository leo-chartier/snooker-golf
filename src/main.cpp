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
    std::vector<Pocket> pocketList = {Pocket(Vector2f(12, 12), 2), // TEMP : Set the hole radius to 2 for now but should be tied to mouth size
                            };

    CueBall cueBall = CueBall(Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2), BALL_RADIUS, CUE_BALL_COLOR);

    vector<Ball> ballsList;
    for (int i = 0; i < 15; i++) {
        Ball ball = Ball(Vector2f(0, 0), BALL_RADIUS, BALL_COLOR);
        ballsList.push_back(ball);
    }

    // Set the position of the balls
    ballsList[0].Position = Vector2f(CLASSIC_WIDTH * 3 / 4, CLASSIC_HEIGHT / 2);
    ballsList[1].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 2 * BALL_RADIUS, CLASSIC_HEIGHT / 2 + BALL_RADIUS);
    ballsList[2].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 2 * BALL_RADIUS, CLASSIC_HEIGHT / 2 - BALL_RADIUS);
    ballsList[3].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 4 * BALL_RADIUS, CLASSIC_HEIGHT / 2 + 2 * BALL_RADIUS);
    ballsList[4].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 4 * BALL_RADIUS, CLASSIC_HEIGHT / 2);
    ballsList[5].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 4 * BALL_RADIUS, CLASSIC_HEIGHT / 2 - 2 * BALL_RADIUS);
    ballsList[6].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 6 * BALL_RADIUS, CLASSIC_HEIGHT / 2 + 3 * BALL_RADIUS);
    ballsList[7].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 6 * BALL_RADIUS, CLASSIC_HEIGHT / 2 + BALL_RADIUS);
    ballsList[8].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 6 * BALL_RADIUS, CLASSIC_HEIGHT / 2 - BALL_RADIUS);
    ballsList[9].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 6 * BALL_RADIUS, CLASSIC_HEIGHT / 2 - 3 * BALL_RADIUS);
    ballsList[10].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 8 * BALL_RADIUS, CLASSIC_HEIGHT / 2 + 4 * BALL_RADIUS);
    ballsList[11].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 8 * BALL_RADIUS, CLASSIC_HEIGHT / 2 + 2 * BALL_RADIUS);
    ballsList[12].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 8 * BALL_RADIUS, CLASSIC_HEIGHT / 2);
    ballsList[13].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 8 * BALL_RADIUS, CLASSIC_HEIGHT / 2 - 2 * BALL_RADIUS);
    ballsList[14].Position = Vector2f(CLASSIC_WIDTH * 3 / 4 + 8 * BALL_RADIUS, CLASSIC_HEIGHT / 2 - 4 * BALL_RADIUS);


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
        cue.setPower(window, &cueBall);
        for (int i = 0; i < ballsList.size(); i++) {
            for (auto& pocket : pocketList) {

            // Check if ball came in contact with any of the pockets
                if (pocket.isBallInPocket(ballsList[i])) {
                    std::cout << "The ball has fallen!" << "\n";
                    ballsList[i].setInactive();
                }

                // Check if cue ball (...)
                if (pocket.isBallInPocket(cueBall)) {
                    std::cout << "The cue ball has fallen!" << "\n";
                    cueBall.setInactive();
                }
            }

            if (cueBall.IsActive()) {
                cueBall.Update(0, dt, ballsList);
            }

            if (ballsList[i].IsActive()) {
                ballsList[i].Update(i, dt, ballsList);
            }
        }
        cueBall.replace();


        // test(&window);
        drawGame(&window, ballsList, &cue,  &cueBall, &table, pocketList, 1); // The number after pocketlist represents the number of pockets to draw
    }

    return 0;
}
