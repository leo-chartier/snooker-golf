#include "display.hpp"

#include "measurements.hpp"
#include "table.hpp"
#include "cue.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>

using namespace sf;

void initializeWindowPosition(RenderWindow* window) {
    float fullTableWidth = CLASSIC_WIDTH + 2 * CLASSIC_OUTER_MARGIN;
    float fullTableHeight = CLASSIC_HEIGHT + 2 * CLASSIC_OUTER_MARGIN;

    float scale = std::min(SCREEN_W / fullTableWidth, SCREEN_H / fullTableHeight);
    float scaledScreenWidth = SCREEN_W / scale;
    float scaledScreenHeight = SCREEN_H / scale;

    Vector2f center = sf::Vector2f(CLASSIC_WIDTH / 2, CLASSIC_HEIGHT + CLASSIC_OUTER_MARGIN - scaledScreenHeight / 2);
    Vector2f size = sf::Vector2f(scaledScreenWidth, scaledScreenHeight);
    View view = View(center, size);
    window->setView(view);
}

void drawGame(RenderWindow* window, Ball* ball, CueBall* cueBall, Table* table, Cue* cue) {
    window->clear();

    table->Draw(window);

    // TODO: Pockets, balls and cue
    window->draw(*ball);
    window->draw(*cueBall);

    // Draw the cue
    cue->Draw(window, *cueBall);

    window->display();
}

void drawLine(RenderWindow* window, Vector2f p1, Vector2f p2, Color color) {
    Vertex line[2] = {
        Vertex(p1, color),
        Vertex(p2, color)
    };
    window->draw(line, 2, sf::Lines);
}