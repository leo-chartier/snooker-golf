#include "table.hpp"

#include "colors.hpp"
#include "display.hpp"
#include "measurements.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Table::Table(Vector2f shapeArray[], size_t length) {
    shapeLength = length;
    shape = new Vector2f[shapeLength];
    for (size_t i = 0; i < shapeLength; i++) {
        shape[i] = shapeArray[i];
    }
}

Table::~Table(void) {
    delete[] shape;
}

void Table::Draw(RenderWindow* window) {
    // TODO: Dynamic display with the shape

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
}