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
                            //Pocket(Vector2f(12, 8), 2),
                            //Pocket(Vector2f(16, 8), 2),
                            //Pocket(Vector2f(20, 8), 2),
                            //Pocket(Vector2f(24, 8), 2),
                            //Pocket(Vector2f(28, 8), 2),
                            //Pocket(Vector2f(32, 8), 2),
                            //Pocket(Vector2f(36, 8), 2),
                            //Pocket(Vector2f(40, 8), 2),
                            //Pocket(Vector2f(44, 8), 2),
                            //Pocket(Vector2f(48, 8), 2),
                            //Pocket(Vector2f(52, 8), 2),
                            //Pocket(Vector2f(56, 8), 2),
                            //Pocket(Vector2f(60, 8), 2),
                            //Pocket(Vector2f(64, 8), 2),
                            //Pocket(Vector2f(68, 8), 2),
                            //Pocket(Vector2f(72, 8), 2),
                            //Pocket(Vector2f(76, 8), 2),
                            //Pocket(Vector2f(80, 8), 2),
                            //Pocket(Vector2f(80, 12), 2),
                            //Pocket(Vector2f(80, 16), 2),
                            //Pocket(Vector2f(80, 20), 2),
                            //Pocket(Vector2f(80, 24), 2),
                            //Pocket(Vector2f(80, 28), 2),
                            //Pocket(Vector2f(80, 32), 2),
                            //Pocket(Vector2f(80, 36), 2),
                            //Pocket(Vector2f(76, 36), 2),
                            //Pocket(Vector2f(72, 36), 2),
                            //Pocket(Vector2f(68, 36), 2),
                            //Pocket(Vector2f(64, 36), 2),
                            //Pocket(Vector2f(60, 36), 2),
                            //Pocket(Vector2f(56, 36), 2),
                            //Pocket(Vector2f(52, 36), 2),
                            //Pocket(Vector2f(48, 36), 2),
                            //Pocket(Vector2f(44, 36), 2),
                            //Pocket(Vector2f(40, 36), 2),
                            //Pocket(Vector2f(36, 36), 2),
                            //Pocket(Vector2f(32, 36), 2),
                            //Pocket(Vector2f(28, 36), 2),
                            //Pocket(Vector2f(24, 36), 2),
                            //Pocket(Vector2f(20, 36), 2),
                            //Pocket(Vector2f(16, 36), 2),
                            //Pocket(Vector2f(12, 36), 2),
                            //Pocket(Vector2f(12, 32), 2),
                            //Pocket(Vector2f(12, 28), 2),
                            //Pocket(Vector2f(12, 24), 2),
                            //Pocket(Vector2f(12, 20), 2),
                            //Pocket(Vector2f(12, 16), 2),
                            //Pocket(Vector2f(12, 12), 2),
                            };

    CueBall cueBall = CueBall(Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2), BALL_RADIUS, CUE_BALL_COLOR);

    vector<Ball> ballsList;
    for (int i = 0; i < 3; i++) {
        Ball ball = Ball(Vector2f(CLASSIC_WIDTH * 3 / 4 + i * 2 * BALL_RADIUS, CLASSIC_HEIGHT / 2), BALL_RADIUS, BALL_COLOR);
        ballsList.push_back(ball);
    }
    // ballsList.push_back(cueBall);

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
