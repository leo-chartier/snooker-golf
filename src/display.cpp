#include "display.hpp"

#include "colors.hpp"
#include "measurements.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f positionToScreen(Vector2f position) {
    float fullTableWidth = CLASSIC_WIDTH + 2 * CLASSIC_OUTER_MARGIN;
    float fullTableHeight = CLASSIC_HEIGHT + 2 * CLASSIC_OUTER_MARGIN;

    float fullScreenWidth = SCREEN_W;
    float fullScreenHeight = fullScreenWidth * fullTableHeight / fullTableWidth;
    if (fullScreenHeight > SCREEN_H) {
        // TODO: Add margin at the top
        fullScreenHeight = SCREEN_H;
        fullScreenWidth = fullScreenHeight * fullTableWidth / fullTableHeight;
    }

    float scale = fullScreenWidth / fullTableWidth;
    float xOffset = (SCREEN_W - CLASSIC_WIDTH * scale) / 2;
    float yOffset = SCREEN_H - (CLASSIC_HEIGHT + CLASSIC_OUTER_MARGIN) * scale;

    return position * scale + Vector2f(xOffset, yOffset);
}

void drawGame(RenderWindow* window) {
    // TODO: Add table as parameter

    window->clear();

    // Draw the rails
    Vector2f railsTL = positionToScreen(Vector2f(
        -CLASSIC_OUTER_MARGIN,
        -CLASSIC_OUTER_MARGIN
    ));
    Vector2f railsBR = positionToScreen(Vector2f(
        CLASSIC_WIDTH + CLASSIC_OUTER_MARGIN,
        CLASSIC_HEIGHT + CLASSIC_OUTER_MARGIN
    ));
    RectangleShape rails = RectangleShape(railsBR - railsTL);
    rails.move(railsTL);
    rails.setFillColor(RAILS_COLOR);
    window->draw(rails);

    // Draw the cloth
    Vector2f clothTL = positionToScreen(Vector2f());
    Vector2f clothBR = positionToScreen(Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT));
    RectangleShape cloth = RectangleShape(clothBR - clothTL);
    cloth.move(clothTL);
    cloth.setFillColor(CLOTH_COLOR);
    window->draw(cloth);

    // TODO: Pockets, balls and cue

    window->display();
}