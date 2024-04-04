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
    RectangleShape rails = RectangleShape(Vector2f(
        CLASSIC_WIDTH + 2 * CLASSIC_OUTER_MARGIN,
        CLASSIC_HEIGHT + 2 * CLASSIC_OUTER_MARGIN
    ));
    rails.move(Vector2f(-CLASSIC_OUTER_MARGIN, -CLASSIC_OUTER_MARGIN));
    rails.setFillColor(RAILS_COLOR);
    window->draw(rails);

    // Draw the cloth
    RectangleShape cloth = RectangleShape(Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT));
    cloth.setFillColor(CLOTH_COLOR);
    window->draw(cloth);
}