#ifndef GAME_DISPLAY
#define GAME_DISPLAY

#include <SFML/Graphics.hpp>

const unsigned int SCREEN_W = 1200;
const unsigned int SCREEN_H = 800;
#define TITLE "SFML TITLE"

float windowScale = 1.0f;

void initializeWindowPosition(sf::Vector2f);
void drawGame(sf::RenderWindow*);
void drawLine(RenderWindow*, Vector2f, Vector2f, Color);

#endif