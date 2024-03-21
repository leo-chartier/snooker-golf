#ifndef GAME_MEASUREMENTS
#define GAME_MESUREMENTS
#include <SFML/Graphics.hpp>

// Sources:
// https://wpapool.com/rules/
// https://billiards.colostate.edu/faq/physics/physical-properties/

// Values in inches for an 8ft table
const float CLASSIC_WIDTH = 96.0f; // 8ft, no cushion
const float CLASSIC_HEIGHT = 48.0f; // 4ft, no cushion
const float CLASSIC_INNER_PADDING = 1.0f;
const float CLASSIC_CORNER_MOUTH = 4.5;
const float CLASSIC_SIDE_MOUTH = 5;
const float CLASSIC_CORNER_ANGLE = 142; // in degrees
const float CLASSIC_SIDE_ANGLE = 104; // in degrees

const float BALL_RADIUS = 1.125f; // in inches
const float BALL_WEIGHT = 170.0f; // in grams
const float BALL_FRICTION_COEFFICIENT = 0.2; // (ball-cloth)

const float CUE_LENGTH = 40.0f; // in inches
const float CUE_TIP_WIDTH = 0.5; // in inches (=14 mm)
const float CUE_BALL_RESTITUTION_COEFFICIENT = 0.8;

#endif