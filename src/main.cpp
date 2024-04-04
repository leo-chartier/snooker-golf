#include "balls.cpp"
#include "display.cpp"
#include "player.cpp"
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "table.cpp"

using namespace std;
using namespace sf;

enum class Scene
{
    MainMenu,
    PoolScene
};

int main()
{
    // Initialize the window for pool scene
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE, Style::Close);
    VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    initializeWindowPosition(&window);

    Vector2f shape[] = {
        Vector2f(),
        Vector2f(CLASSIC_WIDTH, 0),
        Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT),
        Vector2f(0, CLASSIC_HEIGHT),
    };
    Table table = Table(shape, 4);

    CueBall cueBall = CueBall(Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2), BALL_RADIUS, CUE_BALL_COLOR);
    Ball ball = Ball(Vector2f(CLASSIC_WIDTH * 3 / 4, CLASSIC_HEIGHT * 0.51), BALL_RADIUS, BALL_COLOR);

    Player player = Player(0, 0);
    ScoreBoard score = ScoreBoard(player);

    sf::Clock clock;

    // TEMP
    // This has to be fixed as it launches the ball before seing the scene
    cueBall.Velocity.x = 150.0f;

    // Main menu scene objects initialization
    // Create font
    Font font;
    if (!font.loadFromFile("assets/arial.ttf")) // Change the path to your font file
    {
        std::cerr << "Error loading font file" << std::endl;
        return 1;
    }

    // Create main menu background image
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/menu-background.jpg"))
    {
        std::cerr << "Error loading main menu background file" << std::endl;
        return 1;
    }

    Sprite background(backgroundTexture);
    background.setOrigin(background.getLocalBounds().width/20, background.getLocalBounds().height / 4);

        // Get the size of the window and the texture
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // Calculate scale factors
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(0.075, 0.075);

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
    option1.setCharacterSize(45);
    option2.setCharacterSize(45);
    option3.setCharacterSize(45);

    option1.setScale(0.1f, 0.1f);
    option2.setScale(0.1f, 0.1f);
    option3.setScale(0.1f, 0.1f);

    // Set positions for menu options
    option1.setPosition(20, 6);
    option2.setPosition(20, 16);
    option3.setPosition(20, 26);

    // Set colors for menu options
    option1.setFillColor(Color::White);
    option2.setFillColor(Color::White);
    option3.setFillColor(Color::White);

    // Scene choosing
    // By default, we start the game on the main menu to choose the game we are going to play

    Scene currentScene = Scene::MainMenu;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (currentScene == Scene::MainMenu)
                {
                    if (option1.getGlobalBounds().contains(mousePos))
                    {
                        currentScene = Scene::PoolScene;
                    }
                    else if (option2.getGlobalBounds().contains(mousePos))
                    {
                        cout << "Scene 2" << endl;
                    }
                    else if (option3.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
            }
        }

        if (currentScene == Scene::MainMenu)
        {
            window.clear();
            window.draw(background);
            window.draw(option1);
            window.draw(option2);
            window.draw(option3);
            window.display();
        }
        else if (currentScene == Scene::PoolScene)
        {
            // Processing here
            float dt = clock.restart().asSeconds();
            // cue.setPower(window, &cueBall);
            cueBall.Update(dt, &ball);
            ball.Update(dt, &cueBall);
            // test(&window);
            drawGame(&window, &ball, &cueBall, &table, &score);
        }
    }
    return 0;
}

void test(RenderWindow *window)
{
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