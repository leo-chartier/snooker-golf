#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "measurements.hpp"

using namespace sf;

typedef struct map{
    std::vector<Vector2f> borderPoints;
    Vector2f cueBallStart;
    Vector2f ballsStart;
    std::vector<Vector2f> pocketsPositions;
}map_t;

enum Map {
    CLASSIC,
    LOOP,
    M,
    NB_MAPS,
};

map_t maps[] = {
    [CLASSIC] = {
        {
            Vector2f(0, 0),
            Vector2f(CLASSIC_WIDTH, 0),
            Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT),
            Vector2f(0, CLASSIC_HEIGHT),
        },
        Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2),
        Vector2f(CLASSIC_WIDTH * 3 / 4, CLASSIC_HEIGHT / 2),
        {
            Vector2f(POCKET_RADIUS, POCKET_RADIUS),
            Vector2f(CLASSIC_WIDTH / 2, POCKET_RADIUS),
            Vector2f(CLASSIC_WIDTH - POCKET_RADIUS, POCKET_RADIUS),
            Vector2f(CLASSIC_WIDTH - POCKET_RADIUS, CLASSIC_HEIGHT - POCKET_RADIUS),
            Vector2f(CLASSIC_WIDTH / 2, CLASSIC_HEIGHT - POCKET_RADIUS),
            Vector2f(POCKET_RADIUS, CLASSIC_HEIGHT - POCKET_RADIUS),
        }
    },
    [LOOP] = {
        {
            Vector2f(0, 72),
            Vector2f(96, 72),
            Vector2f(96, 44.29),
            Vector2f(91.03, 40.97),
            Vector2f(85.825, 33.185),
            Vector2f(84, 24),
            Vector2f(85.825, 14.815),
            Vector2f(91.03, 7.03),
            Vector2f(98.815, 1.825),
            Vector2f(108, 0),
            Vector2f(117.185, 1.825),
            Vector2f(124.97, 7.03),
            Vector2f(130.175, 14.815),
            Vector2f(132, 24),
            Vector2f(130.175, 33.185),
            Vector2f(124.97, 40.97),
            Vector2f(120, 44.29),
            Vector2f(120, 72),
            Vector2f(132, 72),
            Vector2f(145.775, 74.74),
            Vector2f(157.455, 82.545),
            Vector2f(165.26, 94.225),
            Vector2f(168, 108),
            Vector2f(165.26, 121.78),
            Vector2f(157.455, 133.455),
            Vector2f(145.775, 141.26),
            Vector2f(132, 144),
            Vector2f(118.22, 141.26),
            Vector2f(106.545, 133.455),
            Vector2f(98.74, 121.78),
            Vector2f(96, 108),
            Vector2f(96, 96),
            Vector2f(0, 96),
        },
        Vector2f(12, 84),
        Vector2f(12 + 24, 84),
        {
            Vector2f(108, 24),
        },
    },
    [M] = {
        {
            Vector2f(4, 0),
            Vector2f(92, 0),
            Vector2f(96, 4),
            Vector2f(96, 48),
            Vector2f(80, 48),
            Vector2f(60, 24),
            Vector2f(60, 44),
            Vector2f(56, 48),
            Vector2f(40, 48),
            Vector2f(36, 44),
            Vector2f(36, 24),
            Vector2f(16, 48),
            Vector2f(0, 48),
            Vector2f(0, 4),
        },
        Vector2f(48, 36),
        Vector2f(48, 24),
        {
            Vector2f(POCKET_RADIUS, 48-POCKET_RADIUS),
            Vector2f(96-POCKET_RADIUS, 48-POCKET_RADIUS),
        }
    }
};