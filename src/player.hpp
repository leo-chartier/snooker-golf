#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Player {
protected:
    unsigned short Score;
    unsigned short ShootCount;

public:
    Player(unsigned short score = 0, unsigned short shootCount = 0) : Score(score), ShootCount(shootCount) {}

    void setScore(unsigned short score) {
        Score = score;
    }

    void setShootCount(unsigned short shootCount) {
        ShootCount = shootCount;
    }

    unsigned short getScore() const {
        return Score;
    }

    unsigned short getShootCount() const {
        return ShootCount;
    }
};

class ScoreBoard : public sf::Text {
private:
    Player& player; // Reference to the player object
    sf::Font font; // Font object

public:
    ScoreBoard(Player& playerRef) : player(playerRef) {
        if (!font.loadFromFile("assets/arial.ttf")) {
            std::cout << "Font loading failed" << std::endl;
        }
        setFont(font);
        setCharacterSize(25);
        setFillColor(sf::Color::White);
        setPosition(0, -15);
        updateScore(); // Update the score initially
    }

    void updateScore() {
        setString("Your score: " + std::to_string(player.getScore()));
    }
};

#endif