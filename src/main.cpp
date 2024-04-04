#include <math.h>
#include <time.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "balls.cpp"
#include "cue.cpp"
#include "display.cpp"
#include "player.cpp"
#include "pocket.cpp"
#include "table.cpp"

using namespace std;
using namespace sf;

enum class Scene {
    MainMenu,
    PoolScene
};

int main() {
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE, Style::Close);
    VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));

    Vector2f vertices[] = {
        Vector2f(0, 144),
        Vector2f(192, 144),
        Vector2f(192, 88.58),
        Vector2f(182.06, 81.94),
        Vector2f(171.65, 66.37),
        Vector2f(168, 48),
        Vector2f(171.65, 29.63),
        Vector2f(182.06, 14.06),
        Vector2f(197.63, 3.65),
        Vector2f(216, 0),
        Vector2f(234.37, 3.65),
        Vector2f(249.94, 14.06),
        Vector2f(260.35, 29.63),
        Vector2f(264, 48),
        Vector2f(260.35, 66.37),
        Vector2f(249.94, 81.94),
        Vector2f(240, 88.58),
        Vector2f(240, 144),
        Vector2f(264, 144),
        Vector2f(291.55, 149.48),
        Vector2f(314.91, 165.09),
        Vector2f(330.52, 188.45),
        Vector2f(336, 216),
        Vector2f(330.52, 243.56),
        Vector2f(314.91, 266.91),
        Vector2f(291.55, 282.52),
        Vector2f(264, 288),
        Vector2f(236.44, 282.52),
        Vector2f(213.09, 266.91),
        Vector2f(197.48, 243.56),
        Vector2f(192, 216),
        Vector2f(192, 192),
        Vector2f(0, 192),
    };
    size_t nVertices = sizeof(vertices) / sizeof(Vector2f);
    Table table = Table(vertices, nVertices);

    // The list of pockets
    std::vector<Pocket> pocketList = {
        Pocket(Vector2f(216, 48), 2),  // TEMP : Set the hole radius to 2 for now but should be tied to mouth size
    };

    CueBall cueBall = CueBall(Vector2f(24, 168), BALL_RADIUS, CUE_BALL_COLOR);

    double x0 = cueBall.Position.x + 48.0;
    double y0 = cueBall.Position.y;
    vector<Ball> ballsList;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            double x = x0 + i * BALL_RADIUS * sqrt(3);
            double y = y0 + (j * 2 - i) * BALL_RADIUS;
            Ball ball = Ball(Vector2f(x, y), BALL_RADIUS, BALL_COLOR);
            ballsList.push_back(ball);
        }
    }

    Cue cue = Cue(cueBall.Position, Vector2f(0, 0), 0, 0);

    Player player = Player(0, 0);
    ScoreBoard score = ScoreBoard(player);

    sf::Clock clock;

    // Music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/sounds/tatum.ogg"))  // Use your music file path here
    {
        return -1;  // Error loading the file
    }

    backgroundMusic.setLoop(true);  // Make the music loop
    backgroundMusic.play();

    // Music
    sf::Music ambienceCrowd;
    if (!ambienceCrowd.openFromFile("assets/sounds/ambience.ogg"))  // Use your music file path here
    {
        return -1;  // Error loading the file
    }

    ambienceCrowd.setLoop(true);  // Make the music loop
    ambienceCrowd.play();
    ambienceCrowd.setVolume(40.0f);

    // Main menu scene objects initialization
    // Create font
    Font font;
    // Change the path to your font file
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return 1;
    }

    Font font2;
    // Change the path to your font file
    if (!font.loadFromFile("assets/signalbq.otf")) {
        std::cerr << "Error loading font file" << std::endl;
        return 1;
    }

    // Create main menu background image
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/menu-background.jpg")) {
        std::cerr << "Error loading main menu background file" << std::endl;
        return 1;
    }

    Sprite background(backgroundTexture);

    // Calculate window size
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float menuWidth = textureSize.x;
    float menuHeight = menuWidth * SCREEN_H / SCREEN_W;
    if (menuHeight > textureSize.y) {
        menuHeight = textureSize.y;
        menuWidth = menuHeight * SCREEN_W / SCREEN_H;
    }

    View menuView = View(
        Vector2f(menuWidth / 2, menuHeight / 2),
        Vector2f(menuWidth, menuHeight)
    );
    window.setView(menuView);

    // Create menu options
    Text option1;
    Text option2;
    Text option3;

    // Set text for menu options
    option1.setFont(font);
    option2.setFont(font);
    option3.setFont(font);

    option1.setString("Play Pool");
    option2.setString("Play together");
    option3.setString("Exit");

    // Set character size for menu options
    option1.setCharacterSize(37);
    option2.setCharacterSize(37);
    option3.setCharacterSize(37);

    // Set positions for menu options
    option1.setPosition(20, 30);
    option2.setPosition(20, 100);
    option3.setPosition(20, 170);

    // Set colors for menu options
    option1.setFillColor(Color::White);
    option2.setFillColor(Color::White);
    option3.setFillColor(Color::White);

    // Scene choosing
    // By default, we start the game on the main menu to choose the game we are going to play

    Scene currentScene = Scene::MainMenu;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (currentScene == Scene::MainMenu) {
                    if (option1.getGlobalBounds().contains(mousePos)) {
                        currentScene = Scene::PoolScene;
                        initializeWindowPosition(&window, table);
                    } else if (option2.getGlobalBounds().contains(mousePos)) {
                        cout << "Scene 2" << endl;
                    } else if (option3.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
            }
        }

        if (currentScene == Scene::MainMenu) {
            window.clear();
            window.draw(background);
            window.draw(option1);
            window.draw(option2);
            window.draw(option3);
            window.display();
        } else if (currentScene == Scene::PoolScene) {
            // Lower the music for more focus
            backgroundMusic.setVolume(40.0f);
            ambienceCrowd.setVolume(15.0f);

            // Processing here
            float dt = clock.restart().asSeconds();
            // Check collision with each hole
            cue.setPower(window, &cueBall, ballsList);
            for (int i = 0; i < ballsList.size(); i++) {
                for (auto &pocket : pocketList) {
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
                    cueBall.Update(dt, ballsList, vertices, nVertices);
                }

                if (ballsList[i].IsActive()) {
                    ballsList[i].Update(dt, ballsList, vertices, nVertices);
                }
            }
            cueBall.replace();

            // test(&window);
            drawGame(&window, ballsList, &cue, &cueBall, &table, pocketList, &score);  // The number after pocketlist represents the number of pockets to draw
        }
    }
    return 0;
}