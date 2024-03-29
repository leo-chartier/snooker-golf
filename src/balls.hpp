#ifndef GAME_BALLS
#define GAME_BALLS
#include <SFML/Graphics.hpp>
#include <iostream>

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

    void Update(float dt, Ball* otherBall) {
        Vector2f newPosition = Position;
        Vector2f forceFriction = BALL_FRICTION_COEFFICIENT * BALL_WEIGHT * ACCELERATION_DUE_TO_GRAVITY * normalize(Velocity);
        Vector2f forceAdditional = Vector2f(); // None for now
        Vector2f acceleration = (forceAdditional - forceFriction) / BALL_WEIGHT;

        Velocity += acceleration * dt;
        if (vectorLength(Velocity) <= MIN_VELOCITY)
            Velocity.x = Velocity.y = 0;
        newPosition += Velocity * dt;

        // Collision with the rails
        if (newPosition.x < BALL_RADIUS) {
            newPosition.x = 2 * BALL_RADIUS - newPosition.x;
            Velocity.x = -Velocity.x;
        }
        if (newPosition.x > CLASSIC_WIDTH - BALL_RADIUS) {
            newPosition.x = 2 * (CLASSIC_WIDTH - BALL_RADIUS) - newPosition.x;
            Velocity.x = -Velocity.x;
        }
        if (newPosition.y < BALL_RADIUS) {
            newPosition.y = 2 * BALL_RADIUS - newPosition.y;
            Velocity.y = -Velocity.y;
        }
        if (newPosition.y > CLASSIC_HEIGHT - BALL_RADIUS) {
            newPosition.y = 2 * (CLASSIC_HEIGHT - BALL_RADIUS) - newPosition.y;
            Velocity.y = -Velocity.y;
        }

        // Check for collisions with the other balls
        Vector2f projection = project(otherBall->Position, Position, newPosition);
        float distanceToProjection = vectorLength(otherBall->Position - projection);
        if (distanceToProjection < 2 * BALL_RADIUS) {
            // Calculate the position at which the collision takes place
            Vector2f direction = normalize(newPosition - Position);
            float diameter2 = 4 * BALL_RADIUS * BALL_RADIUS;
            float offsetFromProjection = sqrt(diameter2 - distanceToProjection * distanceToProjection);
            Vector2f hit = projection - direction * offsetFromProjection;

            // Calculate the new velocities for both balls
            Vector2f relativePosition = otherBall->Position - hit;
            Vector2f relativeVelocity = otherBall->Velocity - Velocity;
            float dotProduct = relativeVelocity.x * relativePosition.x + relativeVelocity.y * relativePosition.y;
            float factor = dotProduct / diameter2;
            Vector2f v1 = Velocity + factor * relativePosition;
            Vector2f v2 = otherBall->Velocity + factor * relativePosition;

            // Update the positions
            float remainingFactor = vectorLength(newPosition - Position) / vectorLength(newPosition - hit);
            newPosition = hit + v1 * dt * remainingFactor;
            otherBall->Position += v2 * dt * remainingFactor;
            otherBall->setPosition(otherBall->Position);
            Velocity = v1;
            otherBall->Velocity = v2;
        }

        Position = newPosition;
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