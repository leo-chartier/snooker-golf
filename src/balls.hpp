#ifndef GAME_BALLS
#define GAME_BALLS
#include <SFML/Graphics.hpp>

#include "measurements.hpp"
#include "utils.cpp"

using namespace sf;

float MIN_VELOCITY = 0.01;

class Ball : public CircleShape {
    public:
    Vector2f Position;
    Vector2f Velocity;
    Color BallColor;
    float Radius;
    float Mass;

    Ball(Vector2f p, double r, Color c) : Position(p), Radius(r), BallColor(c) {
        setRadius(r);
        setOrigin(Vector2f(r, r));
        move(p);
        setFillColor(c);
    }

    void Update(float dt) {
        Vector2f forceFriction = BALL_FRICTION_COEFFICIENT * BALL_WEIGHT * ACCELERATION_DUE_TO_GRAVITY * normalize(Velocity);
        Vector2f forceAdditional = Vector2f(); // None for now
        Vector2f acceleration = (forceAdditional - forceFriction) / BALL_WEIGHT;

        Velocity += acceleration * dt;
        if (vectorLength(Velocity) <= MIN_VELOCITY)
            Velocity.x = Velocity.y = 0;
        Position += Velocity * dt;

        // Collision with the rails
        if (Position.x < BALL_RADIUS) {
            Position.x = 2 * BALL_RADIUS - Position.x;
            Velocity.x = -Velocity.x;
        }
        if (Position.x > CLASSIC_WIDTH - BALL_RADIUS) {
            Position.x = 2 * (CLASSIC_WIDTH - BALL_RADIUS) - Position.x;
            Velocity.x = -Velocity.x;
        }
        if (Position.y < BALL_RADIUS) {
            Position.y = 2 * BALL_RADIUS - Position.y;
            Velocity.y = -Velocity.y;
        }
        if (Position.y > CLASSIC_HEIGHT - BALL_RADIUS) {
            Position.y = 2 * (CLASSIC_HEIGHT - BALL_RADIUS) - Position.y;
            Velocity.y = -Velocity.y;
        }

        setPosition(Position);
    }
};

class CueBall : public Ball {
    public:
    CueBall(Vector2f p, double r, Color c) : Ball(p, r, c) {}

    void Hit(Vector2f direction) {
        Velocity = direction * 1000.f;
    }
};

#endif