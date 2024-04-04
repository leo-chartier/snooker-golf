#ifndef BALLS_HPP
#define BALLS_HPP

#include <vector>
#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "measurements.hpp"
#include "colors.hpp"
#include "utils.cpp"

using namespace sf;

float MIN_VELOCITY = 0.01f;
float MAX_VELOCITY = 100.f;

class Ball : public CircleShape {
    public:
    Vector2f Position;
    Vector2f Velocity;
    Color BallColor;
    float Radius;
    float Mass;
    bool isActive = true;

    Ball(Vector2f p, double r, Color c) : Position(p), Radius(r), BallColor(c) {
        setRadius(r);
        setOrigin(Vector2f(r, r));
        move(p);
        setFillColor(c);
    }
    
    void setInactive() {
        isActive = false;
        Velocity = Vector2f(0, 0);
    }

    bool IsActive() const {
        return isActive;
    }

    void Update(float dt, std::vector<Ball>& balls, std::vector<Vector2f> tablePoints) {
        Vector2f newPosition = Position;
        Vector2f forceFriction = BALL_FRICTION_COEFFICIENT * BALL_WEIGHT * ACCELERATION_DUE_TO_GRAVITY * normalize(Velocity);
        Vector2f forceAdditional = Vector2f(); // None for now
        Vector2f acceleration = (forceAdditional - forceFriction) / BALL_WEIGHT;

        Velocity += acceleration * dt;
        if (vectorLength(Velocity) <= MIN_VELOCITY)
            Velocity.x = Velocity.y = 0;
        newPosition += Velocity * dt;

        // Collision with the rails
        if (Velocity.x != 0 || Velocity.y != 0) {
            Vector2f intersection;
            Vector2f direction = normalize(Velocity);
            Vector2f extendedNewPos = newPosition + BALL_RADIUS * direction;
            for (size_t i = 0; i < tablePoints.size(); i++) {
                Vector2f p1 = tablePoints[i];
                Vector2f p2 = tablePoints[(i + 1) % tablePoints.size()];
                if (intersects(p1, p2, Position, extendedNewPos, intersection)) {
                    intersection -= BALL_RADIUS * direction; // TODO: Scale BALL_RADIUS to be the projection on the norm, not the direction directly
                    Vector2f segment = normalize(p2 - p1);
                    Vector2f normal = Vector2f(-segment.y, segment.x); // Rotate 90° counterclockwise to face outside
                    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
                    Velocity -= 2 * dotProduct(Velocity, normal) * normal;
                    float removedDistance = vectorLength(newPosition - intersection);
                    newPosition = intersection + removedDistance * normalize(Velocity);
                    break;
                };
            }
        }

        // Collision with other balls
        for (auto& ball : balls) {
            if (&ball != this && ball.IsActive()) {
                float distance = vectorLength(newPosition - ball.Position);
                if (distance <= 2 * BALL_RADIUS) {
                    Vector2f normal = normalize(newPosition - ball.Position);
                    Vector2f relativeVelocity = Velocity - ball.Velocity;
                    float impulse = (2.f * BALL_WEIGHT * dotProduct(relativeVelocity, normal)) / (2 * BALL_WEIGHT);
                    Velocity -= impulse * normal;
                    ball.Velocity += impulse * normal;
                    newPosition += (2 * BALL_RADIUS - distance) * normal;
                }
            }
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

    void replace(){
        if (!isActive){
            isActive = true;
            Position = Vector2f(CLASSIC_WIDTH / 4, CLASSIC_HEIGHT / 2);
            Velocity = Vector2f(0, 0);
            setPosition(Position);
        }
    }
};

#endif