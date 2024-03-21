#include <math.h>

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define SCREEN_W 1200
#define SCREEN_H 800
#define TITLE "SFML TITLE"

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

        window.clear();
        // Display here
        window.display();
    }

    return 0;
}