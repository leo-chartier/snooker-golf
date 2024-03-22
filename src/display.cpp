#include "display.hpp"

#include "measurements.hpp"
#include "table.hpp"
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

void drawGame(RenderWindow* window, Table* table) {
    window->clear();

    table->Draw(window);

    // TODO: Pockets, balls and cue

    window->display();
}