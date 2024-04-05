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
#include "map.hpp"
#include "table.cpp"

using namespace std;
using namespace sf;

enum class Scene {
    MainMenu,
    PoolScene
};

Table* table;
std::vector<Pocket> pocketList;
CueBall* cueBall;
vector<Ball> ballsList;
Cue* cue;
Player player;

void reset(map_t map) {
    table = new Table(map.borderPoints);

    // The list of pockets
    pocketList.clear();
    for (Vector2f position : map.pocketsPositions) {
        pocketList.push_back(Pocket(position, POCKET_RADIUS));
    }

    cueBall = new CueBall(map.cueBallStart, BALL_RADIUS, CUE_BALL_COLOR);

    Vector2f u = normalize(map.ballsStart - map.cueBallStart);
    Vector2f v = Vector2f(u.y, -u.x);
    ballsList.clear();
    const float brsqrt3 = BALL_RADIUS * sqrt(3);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            Vector2f du = i * brsqrt3 * u;
            Vector2f dv = (j * 2 - i) * BALL_RADIUS * v;
            Vector2f position = map.ballsStart + du + dv;
            Ball ball = Ball(position, BALL_RADIUS, BALL_COLOR);
            ballsList.push_back(ball);
        }
    }

    cue = new Cue(map.cueBallStart);

    player = Player(0, 0);
}

int main() {
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE, Style::Close);
    VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));

    srand(time(NULL));
    size_t mapIndex = NB_MAPS;
    map_t map;

    ScoreBoard score = ScoreBoard(player);

    int pocketedBalls = 0;

    sf::Clock clock;

    

    // Music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/sounds/tatum.ogg")) 
    {
        return -1;  // Error loading the file
    }

    backgroundMusic.setLoop(true);  // Make the music loop
    backgroundMusic.play();

    // Ambience Crowd
    sf::Music ambienceCrowd;
    if (!ambienceCrowd.openFromFile("assets/sounds/ambience.ogg"))
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

    // Ball pocketed
    sf::SoundBuffer ballPocketedBuffer;
    sf::Sound ballPocketedSound;

    if (!ballPocketedBuffer.loadFromFile("assets/sounds/ball_in.ogg")) {
        std::cerr << "Error loading ball in hit sound effect" << std::endl;
        return -1;
    }

    ballPocketedSound.setBuffer(ballPocketedBuffer);
    ballPocketedSound.setVolume(100.f);

    /*
    // ... ball hit
    sf::SoundBuffer ballHitBuffer;
    sf::Sound ballHitSound;

    if (!ballHitBuffer.loadFromFile("assets/sounds/cueball_plus_one.ogg")) {
        std::cerr << "Error loading ball hit sound effect" << std::endl;
        return -1;
    }

    // Multiple balls hit
    sf::SoundBuffer multipleBallsHitBuffer;
    sf::Sound multipleBallsHitSound;

    if (!multipleBallsHitBuffer.loadFromFile("assets/sounds/cue_ball_multiple.ogg")) {
        std::cerr << "Error loading multiple balls hit sound effect" << std::endl;
        return -1;
    }

    */

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
                        size_t oldMap = mapIndex;
                        do {
                            mapIndex = rand() % NB_MAPS;
                        } while (mapIndex == oldMap);
                        map = maps[mapIndex];
                        reset(map);
                        initializeWindowPosition(&window, *table);
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
            cue->setPower(window, cueBall, ballsList);
            for (int i = 0; i < ballsList.size(); i++) {
                for (auto &pocket : pocketList) {
                    // Check if ball came in contact with any of the pockets
                    if (pocket.isBallInPocket(ballsList[i])) {
                        ballPocketedSound.play();

                        // std::cout << "The ball has fallen!" << "\n";
                        ballsList[i].setInactive();
                    }

                    // Check if cue ball (...)
                    if (pocket.isBallInPocket(*cueBall)) {
                        // std::cout << "The cue ball has fallen!" << "\n";
                        cueBall->setInactive();
                    }
                }

                if (cueBall->IsActive()) {
                    cueBall->Update(dt, ballsList, map.borderPoints);
                }

                if (ballsList[i].IsActive()) {
                    ballsList[i].Update(dt, ballsList, map.borderPoints);
                }
            }
            cueBall->replace(map.cueBallStart);

            for (int i = 0; i< ballsList.size(); i++) {
                if (!ballsList[i].isActive) {
                    pocketedBalls++;
                }
            }

            if (pocketedBalls == 15) {
                currentScene = Scene::MainMenu;
                window.setView(menuView);
                continue;
            }

            player.setScore(pocketedBalls);
            score.updateScore();

            pocketedBalls = 0;

            // test(&window);
            drawGame(&window, ballsList, cue, cueBall, table, pocketList, &score);  // The number after pocketlist represents the number of pockets to draw
        }
    }
    return 0;
}