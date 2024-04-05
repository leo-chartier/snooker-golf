#ifndef GAME_DISPLAY
#define GAME_DISPLAY

#include "balls.hpp"
#include "cue.hpp"
#include "pocket.hpp"
#include "table.hpp"
#include <SFML/Graphics.hpp>

const unsigned int SCREEN_W = 1200;
const unsigned int SCREEN_H = 800;
#define TITLE "Snooker Golf"

float windowScale = 1.0f;

void initializeWindowPosition(sf::Vector2f);
void drawGame(RenderWindow* window, std::vector<Ball> balls, Cue* cue,  CueBall* cueBall, Table* table, std::vector<Pocket> pocketList);
void drawLine(RenderWindow*, Vector2f, Vector2f, Color);

#endif