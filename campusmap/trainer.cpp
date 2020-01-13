#include "trainer.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
#include <list>
#include <random>
using namespace std;

Trainer::Trainer( float Speed, int sheetRect, int sizeAnim) {

    if (!texturePlayer.loadFromFile(/* resourcePath() + */ "Sprites/trainer.png")) {
        std::cout << "Error loading sprite";
    }
    (spritePlayer).setTexture(texturePlayer);

    (spritePlayer).setTextureRect(sf::IntRect(2,2,sheetRect,sheetRect));
    //spritePlayer.setScale(sf::Vector2f(0.50f, 0.50f));
    //spritePlayer.setPosition(264, 272);

    playerMovementSpeed = Speed;
    this->sheetRect = sheetRect;
    this->sizeAnim = sizeAnim;
    speedSprite = 0;

    font.loadFromFile("Fonts/sansation.ttf");

    fish = true;
//    fight_mode = 'w';
}

void Trainer::draw(sf::RenderWindow &window, sf::Event &event, sf::View &view) {
    window.draw(spritePlayer);
    displacement(event,view);
    fishing(window, view); //To put in map after condition of state fishing
                           //because there's a problem of order of drawing with Npc
    rock(window, view);
}

void Trainer::setSpeed(sf::Event &event) {
    if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift))) {
        playerMovementSpeed = 4;
        speedSprite = 340;
    }
    if ((event.type == sf::Event::KeyReleased)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift))) {
        playerMovementSpeed = 2;
        speedSprite = 0;
    }
}
sf::Vector2f Trainer::getPos() {
    sf::Vector2f position = (spritePlayer).getPosition();
    return position;
}

void Trainer::displacement(sf::Event &event, sf::View &view) {
    sf::Vector2f position = (spritePlayer).getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    setSpeed(event);
    if (state == "Walking") {
        if(intern_clock.getElapsedTime().asMilliseconds() >= (float) 2000/30){
            if (facingDirection == "Down") {
                if (y >= b + 16) {
                    state = "Stop";
                    (spritePlayer).setTextureRect(sf::IntRect(2,2,sheetRect,sheetRect));
                    counterWalk = 1;
                }
                else{
                    (spritePlayer).move(0, playerMovementSpeed);
                    (spritePlayer).setTextureRect(sf::IntRect(2 + counterWalk * (sheetRect+2)+speedSprite,2,sheetRect,sheetRect));
                    view.move(0,playerMovementSpeed);

                    counterWalk++;
                    if(counterWalk==sizeAnim){
                        counterWalk = 0;
                    }
                }
            }
            if (facingDirection == "Up") {
                if ( y <= b - 16){
                    state = "Stop";
                    counterWalk = 1;
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2 + (sheetRect+2),sheetRect,sheetRect));
                }
                else{
                    (spritePlayer).move(0, -playerMovementSpeed);
                    (spritePlayer).setTextureRect(sf::IntRect(2 + counterWalk * (2 + sheetRect)+speedSprite,2 + (sheetRect+2),sheetRect,sheetRect));
                    view.move(0, -playerMovementSpeed);

                    counterWalk++;
                    if(counterWalk == sizeAnim){
                        counterWalk = 0;
                     }
                }
            }
            if (facingDirection == "Right") {
                if (x >= a + 16){// -10 because of initial position
                        state = "Stop";
                        counterWalk = 1;
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2+ 3*(sheetRect+2),sheetRect,sheetRect));
                }
                else{
                    (spritePlayer).move(playerMovementSpeed, 0);
                    (spritePlayer).setTextureRect(sf::IntRect(2+counterWalk * (sheetRect+2)+speedSprite,2+ 3*(sheetRect+2),sheetRect,sheetRect));
                    view.move(playerMovementSpeed, 0);

                    counterWalk++;
                    if(counterWalk == sizeAnim){
                        counterWalk = 0;
                     }
                }
            }
            if (facingDirection == "Left") {
                if (x <= a - 16 ){ // because of initial position
                    state = "Stop";
                    counterWalk = 1;
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2+2*(sheetRect+2),sheetRect,sheetRect));
                }
                else{
                    (spritePlayer).move(-playerMovementSpeed, 0);
                    (spritePlayer).setTextureRect(sf::IntRect(2+counterWalk * (sheetRect+2)+speedSprite,2+2*(sheetRect+2),sheetRect,sheetRect));
                    view.move(-playerMovementSpeed, 0);

                    counterWalk++;
                    if(counterWalk == sizeAnim){
                        counterWalk = 0;
                    }
                }
            }
                intern_clock.restart();
        }
        else{
            if (facingDirection == "Down") {
                if (y >= b + 16) {
                    state = "Stop";
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2,sheetRect,sheetRect));
                    counterWalk = 1;
                }
                else{
                    (spritePlayer).move(0, playerMovementSpeed);
                    (spritePlayer).setTextureRect(sf::IntRect(2 + counterWalk * (sheetRect+2)+speedSprite,2,sheetRect,sheetRect));
                    view.move(0,playerMovementSpeed);
                }
            }
            if (facingDirection == "Up") {
                if ( y <= b - 16){
                    state = "Stop";
                    counterWalk = 1;
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2+sheetRect+2,sheetRect,sheetRect));
                }
                else{
                    (spritePlayer).move(0, -playerMovementSpeed);
                    (spritePlayer).setTextureRect(sf::IntRect(2+counterWalk * (sheetRect+2)+speedSprite,2+sheetRect+2,sheetRect,sheetRect));
                    view.move(0, -playerMovementSpeed);
                }
            }
            if (facingDirection == "Right") {
                if (x >= a + 16){// -10 because of initial position
                        state = "Stop";
                        counterWalk = 1;
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2+3*(sheetRect+2),sheetRect,sheetRect));
                }
                else{
                    (spritePlayer).move(playerMovementSpeed, 0);
                    (spritePlayer).setTextureRect(sf::IntRect(2+counterWalk * (sheetRect+2)+speedSprite,2+3*(sheetRect+2),sheetRect,sheetRect));
                    view.move(playerMovementSpeed, 0);
                }
            }

            if (facingDirection == "Left") {
                if (x <= a - 16 ){ // because of initial position
                    state = "Stop";
                    counterWalk = 1;
                    (spritePlayer).setTextureRect(sf::IntRect(2+speedSprite,2+2*(sheetRect+2),sheetRect,sheetRect));
                }
                else{
                    (spritePlayer).move(-playerMovementSpeed, 0);
                    (spritePlayer).setTextureRect(sf::IntRect(2+counterWalk * (sheetRect+2)+speedSprite,2+2*(sheetRect+2),sheetRect,sheetRect));
                    view.move(-playerMovementSpeed, 0);
                }
            }
        }
    }
}

sf::FloatRect Trainer::getViewBounds(const sf::View &view)
{
        sf::FloatRect rt;
        rt.left = view.getCenter().x - view.getSize().x/2.f;
        rt.top  = view.getCenter().y - view.getSize().y/2.f;
        rt.width  = view.getSize().x;
        rt.height = view.getSize().y;
        return rt;
}


void Trainer::fishing(sf::RenderWindow &window, sf::View &view){
    int y = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    if (facingDirection == "Down"){
        y = 0;
        c = 1;
        d = 8;
    }
    else if (facingDirection == "Up"){
        y = 1;
    }
    else if (facingDirection == "Left"){
        y = 2;
        a = -1;
        b = -8;
    }
    else {
        y = 3;
        a = 1;
        b = 8;
    }

    if (state == "Fishing"){

        if (counterWalk < 4){
            (spritePlayer).setTextureRect(sf::IntRect(512 + counterWalk * (sheetRect+2),2+y*(sheetRect+2),sheetRect,sheetRect));
            if (counterWalk == 0){
                (spritePlayer).move(-a,-c);
            }
            if (counterWalk == 2){
                (spritePlayer).move(b,d);
            }
            counterWalk ++;
        }

    }
    if (state == "stopFishing"){
        (spritePlayer).setTextureRect(sf::IntRect(2 + 510 + counterWalk * (sheetRect+2),2 + y*(sheetRect+2),sheetRect,sheetRect));
        if (counterWalk == 1){
            (spritePlayer).move(-b,-d);
        }
        if (counterWalk > 0){
            counterWalk = counterWalk-1;
        }
        else{
            state = "Stop";
            (spritePlayer).setTextureRect(sf::IntRect(2,2+ y*(sheetRect+2),sheetRect,sheetRect));
            (spritePlayer).move(a,c);
            text.setString("");
        }

    }

}


//throw rock
void Trainer::rock(sf::RenderWindow &window, sf::View &view){
    if (state == "Throwing"){
        std::cout << counterWalk << std::endl;
        sf::FloatRect viewBounds = getViewBounds(view);
        text.setFont(font);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);

        bubble.setPointCount(8);
        bubble.setPoint(0, sf::Vector2f(float(viewBounds.left + 30), float(viewBounds.top + viewBounds.height - 60)));
        bubble.setPoint(1, sf::Vector2f(float(viewBounds.left + viewBounds.height - 30), float(viewBounds.top + viewBounds.height - 60)));
        bubble.setPoint(2, sf::Vector2f(float(viewBounds.left + viewBounds.height - 10), float(viewBounds.top + viewBounds.height - 45)));
        bubble.setPoint(3, sf::Vector2f(float(viewBounds.left + viewBounds.height - 10), float(viewBounds.top + viewBounds.height - 25)));
        bubble.setPoint(4, sf::Vector2f(float(viewBounds.left + viewBounds.height - 30), float(viewBounds.top + viewBounds.height - 10)));
        bubble.setPoint(5, sf::Vector2f(float(viewBounds.left + 30), float(viewBounds.top + viewBounds.height - 10)));
        bubble.setPoint(6, sf::Vector2f(float(viewBounds.left + 10), float(viewBounds.top + viewBounds.height - 25)));
        bubble.setPoint(7, sf::Vector2f(float(viewBounds.left + 10), float(viewBounds.top + viewBounds.height - 45)));
        bubble.setOutlineColor(sf::Color::Black);
        bubble.setOutlineThickness(2.f);
        text.setPosition(int(viewBounds.left) + 35, int(viewBounds.top + viewBounds.height - 40) );
        /* bubble.setPosition(int(viewBounds.left), int(viewBounds.top + viewBounds.height - 50)); */

        window.draw(bubble);
        window.draw(text);

        sf::Sprite sprite;
        sprite.setTexture(texturePlayer);
        sprite.setTextureRect(sf::IntRect(2 + ((int) counterWalk/3) *82,322,80,80));
        sprite.setPosition(viewBounds.left + 16,viewBounds.top + viewBounds.height/2 -5);
        window.draw(sprite);
        if (counterWalk < 12){
            counterWalk ++;
            text.setString("");
        }
        else{
            text.setString("Oups, you broke his window...");
        }
    }
}
