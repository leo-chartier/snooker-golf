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


    void Update(float dt, std::vector<Ball>& balls) {
        Vector2f newPosition = Position;
        Vector2f forceFriction = BALL_FRICTION_COEFFICIENT * BALL_WEIGHT * ACCELERATION_DUE_TO_GRAVITY * normalize(Velocity);
        Vector2f forceAdditional = Vector2f(); // None for now
        Vector2f acceleration = (forceAdditional - forceFriction) / BALL_WEIGHT;

        Velocity += acceleration * dt;
        if (vectorLength(Velocity) <= MIN_VELOCITY)
            Velocity.x = Velocity.y = 0;
        newPosition += Velocity * dt;

        // // Collision with the rails
        // TODO: Collision with new walls
        // if (newPosition.x < BALL_RADIUS) {
        //     newPosition.x = 2 * BALL_RADIUS - newPosition.x;
        //     Velocity.x = -Velocity.x;
        // }
        // if (newPosition.x > CLASSIC_WIDTH - BALL_RADIUS) {
        //     newPosition.x = 2 * (CLASSIC_WIDTH - BALL_RADIUS) - newPosition.x;
        //     Velocity.x = -Velocity.x;
        // }
        // if (newPosition.y < BALL_RADIUS) {
        //     newPosition.y = 2 * BALL_RADIUS - newPosition.y;
        //     Velocity.y = -Velocity.y;
        // }
        // if (newPosition.y > CLASSIC_HEIGHT - BALL_RADIUS) {
        //     newPosition.y = 2 * (CLASSIC_HEIGHT - BALL_RADIUS) - newPosition.y;
        //     Velocity.y = -Velocity.y;
        // }

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