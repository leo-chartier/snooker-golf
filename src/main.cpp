#include "display.cpp"
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
    // Initialize the window
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), TITLE);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Processing here

        drawGame(&window);
    }

    return 0;
}