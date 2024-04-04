#include "table.hpp"

#include "colors.hpp"
#include "display.hpp"
#include "measurements.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

float cross(const Vector2f a, const Vector2f b, const Vector2f c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

size_t getPrevious(uint64_t done, size_t index, size_t n) {
    size_t prev = index;
    do {
        prev = (prev - 1 + n) % n;
    } while (done & (1 << prev));
    return prev;
}

size_t getNext(uint64_t done, size_t index, size_t n) {
    size_t next = index;
    do {
        next = (next + 1) % n;
    } while (done & (1 << next));
    return next;
}

bool isEar(const std::vector<Vector2f>& polygon, size_t prev, size_t index, size_t next) {
    return cross(polygon[prev], polygon[index], polygon[next]) > 0;
}

void triangulate(const std::vector<Vector2f>& polygon, ConvexShape* triangles) {
    // TODO: Allow for holes
    int n = polygon.size();
    if (n < 3 || n > 64) return;

    size_t prev, next;

    uint64_t done = 0;
    uint64_t ears = 0;
    for (size_t index = 0; index < n; index++) {
        prev = getPrevious(done, index, n);
        next = getNext(done, index, n);
        ears |= isEar(polygon, prev, index, next) << index;
    }

    int remainingTriangles = n - 2;
    size_t triangleIndex = 0;
    size_t index = 0;
    while (remainingTriangles > 0) {
        uint64_t mask = 1 << index;
        if (ears & mask) {
            prev = getPrevious(done, index, n);
            next = getNext(done, index, n);

            // Output triangle indices
            triangles[triangleIndex].setPoint(0, polygon[prev]);
            triangles[triangleIndex].setPoint(1, polygon[index]);
            triangles[triangleIndex].setPoint(2, polygon[next]);
            triangleIndex++;

            // Remove the ear
            ears &= ~mask;
            done |= mask;
            remainingTriangles--;

            // Update neighbors
            ears &= ~((1 << prev) | (1 << next));
            ears |= isEar(polygon, getPrevious(done, prev, n), prev, index) << prev;
            ears |= isEar(polygon, index, next, getNext(done, next, n)) << next;
        }
        index = (index + 1) % n;
    }
}

Table::Table(std::vector<Vector2f> points) {
    if (points.size() < 3 || points.size() > 64) perror("Must have between 3 and 64 vertices");
    this->nPoints = points.size();
    this->points = points;
    this->nTriangles = nPoints - 2;
    this->triangles = new ConvexShape[nTriangles];

    for (size_t i = 0; i < nTriangles; i++) {
        ConvexShape triangle(3);
        triangle.setFillColor(CLOTH_COLOR);
        triangles[i] = triangle;
    }
    triangulate(points, triangles);
}

void Table::Draw(RenderWindow* window) {
    // Draw the rails
    // TODO

    // Draw the cloth
    for (size_t index = 0; index < nTriangles; index++) {
        ConvexShape triangle = this->triangles[index];
        window->draw(triangle);
    }
}