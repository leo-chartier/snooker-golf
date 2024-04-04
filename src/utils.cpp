#include <SFML/Graphics.hpp>

#include "utils.hpp"

#include <math.h>

using namespace sf;

float vectorLength(Vector2f vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f normalize(Vector2f vector) {
    float squaredNorm = vector.x * vector.x + vector.y * vector.y;
    if (squaredNorm == 0)
        return Vector2f();
    // float inverseNorm  = squaredNorm;
    // long i  = * ( long * ) &inverseNorm;
    // i  = 0x5f3759df - ( i >> 1 );
    // inverseNorm  = * ( float * ) &i;
    // inverseNorm  = inverseNorm * ( 1.5f - ( squaredNorm * inverseNorm * inverseNorm / 2 ) );
    // return vector * inverseNorm;
    return vector / sqrt(squaredNorm);
}

float dotProduct(Vector2f p1, Vector2f p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

float crossProduct(Vector2f p1, Vector2f p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

Vector2f project(Vector2f point, Vector2f p1, Vector2f p2) {
    Vector2f direction = p2 - p1;
    float lengthSquared = direction.x * direction.x + direction.y * direction.y;
    if (lengthSquared == 0)
        return p1;
    Vector2f diff1 = point - p1;
    float dot = diff1.x * direction.x + diff1.y * direction.y;
    float t = std::clamp(dot / lengthSquared, 0.0f, 1.0f);
    return p1 + t * direction;
}

int orientation(Vector2f p, Vector2f q, Vector2f r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

bool isOnSegment(Vector2f p, Vector2f q, Vector2f r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

// Function to check if two line segments intersect
bool intersects(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2, Vector2f& intersection) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 == o2 || o3 == o4) return false;

    // Calculate intersection point
    float x1 = p1.x, y1 = p1.y;
    float x2 = q1.x, y2 = q1.y;
    float x3 = p2.x, y3 = p2.y;
    float x4 = q2.x, y4 = q2.y;

    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    float numerator_x = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    float x_intersect = numerator_x / denominator;
    float numerator_y = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    float y_intersect = numerator_y / denominator;

    intersection = Vector2f(x_intersect, y_intersect);
    return true;
}