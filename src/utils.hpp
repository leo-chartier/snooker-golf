#include <SFML/Graphics.hpp>

float vectorLength(sf::Vector2f vector);
sf::Vector2f normalize(sf::Vector2f);
float distanceToSegment(sf::Vector2f, sf::Vector2f, sf::Vector2f);
sf::Vector2f project(sf::Vector2f point, sf::Vector2f p1, sf::Vector2f p2);
bool intersects(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2, sf::Vector2f& intersection);