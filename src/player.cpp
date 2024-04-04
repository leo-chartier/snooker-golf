#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
using namespace std;

class player {
    virtual int (calcScore()) = 0;
    virtual int (shoot()) = 0;
    virtual int (PlaceWhieBall()) = 0;

};

class scoreBoard : player {
    public:
    int score;

    int calcScore(){
        if (ballInHole=1) {
            score = score+1;
            return;
        }
    };

};

class ballPosition : player {
    public:
    int shoot(){
        
        return;
    };

    int Placewhitball(){

        return;
    };

};

int main() {

    sf::RectangleShape rectangle(sf::Vector2f(50, 120));
    scoreBoard P1;
    scoreBoard P2;
    P1.calcScore();
    P2.calcScore();

    // sf::Text text;


    // text.setFont(font);

    // text.setString("Scoreboard :");

    // text.setCharacterSize(24);

    // text.setFillColor(sf::Color::Red);

    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);


}
