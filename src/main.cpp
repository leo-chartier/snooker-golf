#include "display.cpp"
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "table.cpp"
#include "cue.cpp"

using namespace std;
using namespace sf;

int main() {
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE);

    Vector2f shape[] = {
        Vector2f(),
        Vector2f(CLASSIC_WIDTH, 0),
        Vector2f(CLASSIC_WIDTH, CLASSIC_HEIGHT),
        Vector2f(0, CLASSIC_HEIGHT),
    };
    Table table = Table(shape, 4);
    Cue cue = Cue(Vector2f(500, 200), Vector2f(0,0), 0, 0);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Processing here
        cue.setPower(window);
        drawGame(&window, &table, &cue);
    }

    return 0;
}