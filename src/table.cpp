#include "table.hpp"

#include "colors.hpp"
#include "display.hpp"
#include "measurements.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

size_t findFollowing(size_t index, uint64_t mask, size_t length, int direction) {
    for (int offset = 1; offset < length; offset++) {
        size_t newIndex = (index + offset * direction);
        if (newIndex < 0) newIndex += length;
        if (mask & (1 << newIndex)) {
            return newIndex;
        }
    }
    return index;
}

bool isConvex(Vector2f v0, Vector2f v1, Vector2f v2) {
    Vector2f e1 = v1 - v0;
    Vector2f e2 = v2 - v1;
    float crossProduct = (e1.x * e2.y) - (e1.y * e2.x);
    return crossProduct > 0;
}

Table::Table(Vector2f shapeArray[], size_t length) {
    if (length < 3) return; // TODO: Error: Needs at least 3 points
    if (length > 64) return; // TODO: Error: Implementation need at most 64 points
    this->nPoints = length;
    this->points = shapeArray;
    this->nTriangles = length - 2;
    this->triangles = new ConvexShape[nTriangles];

    // Bit mask of the remaining edges to be clipped
    uint64_t remaining = (1 << length) - 1;
    for (int iteration = 0; iteration < nTriangles; iteration++) {
        Vector2f vertex, previousVertex, nextVertex;
        uint64_t vertexMask;
        // Find a valid ear (three consecutive points in clockwise order)
        for (size_t vertexIndex = 0; vertexIndex < length; vertexIndex++) {
            vertexMask = (1 << vertexIndex);
            if (~remaining & vertexMask) continue;
            size_t previousIndex = findFollowing(vertexIndex, remaining, length, -1);
            size_t nextIndex = findFollowing(vertexIndex, remaining, length, 1);
            previousVertex = shapeArray[previousIndex];
            vertex = shapeArray[vertexIndex];
            nextVertex = shapeArray[nextIndex];
            if (isConvex(previousVertex, vertex, nextVertex)) break;
        }
        // Add the triangle
        ConvexShape triangle(3);
        triangle.setPoint(0, previousVertex);
        triangle.setPoint(1, vertex);
        triangle.setPoint(2, nextVertex);
        triangle.setFillColor(CLOTH_COLOR);
        this->triangles[iteration] = triangle;
        remaining &= ~vertexMask;
    }
}

Table::~Table(void) {
    delete[] triangles;
    printf("===== DESTRUCTOR =====\n"); std::flush(std::cout);
}

void Table::Draw(RenderWindow* window) {
    printf("===== TABLE DRAW =====\n"); std::flush(std::cout);
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
    for (size_t index = 0; index < nTriangles; index++) {
        ConvexShape triangle = this->triangles[index];
        printf("===== OK =====\n"); std::flush(std::cout);
        window->draw(triangle);
    }
}