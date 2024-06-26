#include "display.hpp"

#include "measurements.hpp"
#include "table.hpp"
#include "player.cpp"
#include "cue.hpp"
#include "pocket.hpp"
#include "balls.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <vector>

using namespace sf;

void initializeWindowPosition(RenderWindow* window, Table table) {
    float xInnerMin = table.points[0].x;
    float xInnerMax = table.points[0].x;
    float yInnerMin = table.points[0].y;
    float yInnerMax = table.points[0].y;
    // TODO: Use rail points instead
    float xOuterMin = table.points[0].x;
    float xOuterMax = table.points[0].x;
    float yOuterMin = table.points[0].y;
    float yOuterMax = table.points[0].y;

    for (size_t index = 1; index < table.nPoints; index++) {
        float xInner = table.points[index].x;
        float yInner = table.points[index].y;
        // TODO: Use rail points instead
        float xOuter = table.points[index].x;
        float yOuter = table.points[index].y;
        xInnerMin = std::min(xInnerMin, xInner);
        xInnerMax = std::max(xInnerMax, xInner);
        yInnerMin = std::min(yInnerMin, yInner);
        yInnerMax = std::max(yInnerMax, yInner);
        xOuterMin = std::min(xOuterMin, xOuter);
        xOuterMax = std::max(xOuterMax, xOuter);
        yOuterMin = std::min(yOuterMin, yOuter);
        yOuterMax = std::max(yOuterMax, yOuter);
    }

    float tableWidth = xInnerMax - xInnerMin;
    float fullTableWidth = xOuterMax - xOuterMin;
    float tableHeight = yInnerMax - yInnerMin;
    float fullTableHeight = yOuterMax - yOuterMin;

    float scale = std::max(fullTableWidth / SCREEN_W, fullTableHeight / (SCREEN_H * (1 - MIN_HEADER_RATIO)));
    float scaledScreenWidth = SCREEN_W * scale;
    float scaledScreenHeight = SCREEN_H * scale;

    // TODO: If height >>> width
    Vector2f center = Vector2f((xOuterMax + xOuterMin) / 2, tableHeight + CLASSIC_OUTER_MARGIN - scaledScreenHeight / 2);
    Vector2f size = Vector2f(scaledScreenWidth, scaledScreenHeight);
    View view = View(center, size);
    window->setView(view);
}

void drawGame(RenderWindow* window, std::vector<Ball> balls, Cue* cue,  CueBall* cueBall, Table* table, std::vector<Pocket> pocketList, ScoreBoard* score) {
    window->clear();

    table->Draw(window);

    // Draw the pockets
    for (size_t i = 0; i < pocketList.size(); i++){
        pocketList[i].Draw(window);
    }

    // Draw the ball if it's active
    for (int i = 0; i < balls.size(); i++) {
        Ball ball = balls[i];
        if (ball.IsActive()) {
            window->draw(ball);
        }
    }
    
    // Draw the cue ball if it's active
    if (cueBall->IsActive()) {
        window->draw(*cueBall);
    }

    // Draw the cue
    cue->Draw(window, *cueBall, balls);

    window->draw(*score);

    window->display();
}

void drawLine(RenderWindow* window, Vector2f p1, Vector2f p2, Color color) {
    Vertex line[2] = {
        Vertex(p1, color),
        Vertex(p2, color)
    };
    window->draw(line, 2, sf::Lines);
}