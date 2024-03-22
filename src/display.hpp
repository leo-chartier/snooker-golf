#ifndef GAME_DISPLAY
#define GAME_DISPLAY

#include <SFML/Graphics.hpp>

#define SCREEN_W 1200
#define SCREEN_H 800
#define TITLE "SFML TITLE"

sf::Vector2f positionToScreen(sf::Vector2f);
void drawGame(sf::RenderWindow*);

#endif