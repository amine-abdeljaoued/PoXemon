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

Trainer::Trainer( float Speed, int sheetRect, int sizeAnim)
{
    
    if (!texturePlayer.loadFromFile(/* resourcePath() + */ "Sprites/trainer.png")) {
        cout << "Error loading sprite";
    }
    (spritePlayer).setTexture(texturePlayer);

    (spritePlayer).setTextureRect(sf::IntRect(2,2,sheetRect,sheetRect));
    //spritePlayer.setScale(sf::Vector2f(0.50f, 0.50f));
    spritePlayer.setPosition(264, 272);

    playerMovementSpeed = Speed;
    this->sheetRect = sheetRect;
    this->sizeAnim = sizeAnim;
    speedSprite = 0;

    
}

void Trainer::draw(sf::RenderWindow &window) const {
    window.draw(spritePlayer);
}

void Trainer::setSpeed(sf::Event &event){
    if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift)))
    {
        playerMovementSpeed = 4;
        speedSprite = 170;
    }
    if ((event.type == sf::Event::KeyReleased)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift)))
    {
        playerMovementSpeed = 2;
        speedSprite = 0;
    }
}
sf::Vector2f Trainer::getPos(){
    sf::Vector2f position = (spritePlayer).getPosition();
    return position;
}

void Trainer::displacement(sf::Event &event, sf::View &view, const std::string* case_num)
{
    sf::Vector2f position = (spritePlayer).getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    
    setSpeed(event); 

    

    if (state == "Walking")
    {
        if(intern_clock.getElapsedTime().asMilliseconds() >= (float) 2000/30){
        
            if (facingDirection == "Down")
            {
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
            
            if (facingDirection == "Up")
            {
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
            
            if (facingDirection == "Right")
            {
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
            
            if (facingDirection == "Left")
            {
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

            if (facingDirection == "Down")
            {
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

            if (facingDirection == "Up")
            {
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

            if (facingDirection == "Right")
            {
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

            if (facingDirection == "Left")
            {
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
