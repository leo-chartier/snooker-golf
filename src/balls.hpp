#ifndef GAME_BALLS
#define GAME_BALLS
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball : public CircleShape
{
public:
    Vector2f Position;
    Vector2f Velocity;
    Color BallColor;
    float Radius;
    float Mass;

    Ball(Vector2f p, double r, Color c) : Position(p), Radius(r), BallColor(c)
    {
        setRadius(r);
        move(p);
        setFillColor(c);
    }

    void Update(float dt)
    {
        Position += Velocity * dt;
        setPosition(Position);
    }
};

class CueBall : public Ball
{
public:
    CueBall(Vector2f p, double r, Color c) : Ball(p, r, c) {}

    void Hit(Vector2f direction)
    {
        Velocity = direction * 1000.f;
    }
};

#endif