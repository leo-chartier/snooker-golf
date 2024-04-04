#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "pocket.hpp"
#include "balls.hpp"

using namespace sf;

typedef struct map{
    std::vector<Vector2f> borderPoints;
    Vector2f cueBallStart;
    Vector2f ballsStart;
    std::vector<Vector2f> pocketsPositions;
}map_t;

map_t mapLoop {
    {
        Vector2f(0, 144),
        Vector2f(192, 144),
        Vector2f(192, 88.58),
        Vector2f(182.06, 81.94),
        Vector2f(171.65, 66.37),
        Vector2f(168, 48),
        Vector2f(171.65, 29.63),
        Vector2f(182.06, 14.06),
        Vector2f(197.63, 3.65),
        Vector2f(216, 0),
        Vector2f(234.37, 3.65),
        Vector2f(249.94, 14.06),
        Vector2f(260.35, 29.63),
        Vector2f(264, 48),
        Vector2f(260.35, 66.37),
        Vector2f(249.94, 81.94),
        Vector2f(240, 88.58),
        Vector2f(240, 144),
        Vector2f(264, 144),
        Vector2f(291.55, 149.48),
        Vector2f(314.91, 165.09),
        Vector2f(330.52, 188.45),
        Vector2f(336, 216),
        Vector2f(330.52, 243.56),
        Vector2f(314.91, 266.91),
        Vector2f(291.55, 282.52),
        Vector2f(264, 288),
        Vector2f(236.44, 282.52),
        Vector2f(213.09, 266.91),
        Vector2f(197.48, 243.56),
        Vector2f(192, 216),
        Vector2f(192, 192),
        Vector2f(0, 192),
    },
    Vector2f(24, 168),
    Vector2f(24 + 48, 168),
    {
        Vector2f(216, 48),
    },
};