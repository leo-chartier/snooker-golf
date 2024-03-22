#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
using namespace std;

class player {
    virtual int (calcScore()) = 0;
    virtual int (shootNum()) = 0;

};

class scoreBoard : player {
    public:
    int score;
    int shoot;

    int calcScore(){
        if (ballInHole=1) {
            score = score+1;
        }
    };

    int shootNum(){
        if(playerTouchBall=1){
            shoot = shoot+1;
        }
    };

};

class ballPosition : player {
    public:
    int placewhiteball;

};

int main() {

    sf::RectangleShape rectangle(sf::Vector2f(50, 120));
    scoreBoard P1;
    scoreBoard P2;
    P1.calcScore();
    P1.shootNum();
    P2.calcScore();
    P2.shootNum();

    sf :: Text text;


    text.setFont(font);

    text.setString("Scoreboard :");

    text.setCharacterSize(24);

    text.setFillColor(sf::Color::Red);

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);

}
