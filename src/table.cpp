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
    
}