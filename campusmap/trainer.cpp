#include "trainer.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
#include <list>
using namespace std;

Trainer::Trainer( float Speed, int sheetRect, int sizeAnim, int& map_num)
{
    
    if (!texturePlayer.loadFromFile(/* resourcePath() + */ "Sprites/fullch.png")) {
        cout << "Error loading sprite";
    }
    (spritePlayer).setTexture(texturePlayer);

    (spritePlayer).setTextureRect(sf::IntRect(0,0,64,64));
    spritePlayer.setScale(sf::Vector2f(0.5f, 0.5f));
    spritePlayer.setPosition(262, 272);

    playerMovementSpeed = Speed;
    this->sheetRect = sheetRect;
    this->sizeAnim = sizeAnim;
    this->map_num = map_num;

    
}

void Trainer::draw(sf::RenderWindow &window) const {
    window.draw(spritePlayer);
}

void Trainer::setSpeed(sf::Event &event){
    if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift)))
    {
        playerMovementSpeed = 8;
    }
    if ((event.type == sf::Event::KeyReleased)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift)))
    {
        playerMovementSpeed = 4;
    }
}
sf::Vector2f Trainer::getPos(){
    sf::Vector2f position = (spritePlayer).getPosition();
    return position;
}

void Trainer::displacement(sf::Event &event, sf::View &view, const int* collision)
{
    sf::Vector2f position = (spritePlayer).getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
//    std::cout<<x<<","<<y<<std::endl;
    
    setSpeed(event);
    
    if (collision[(int) x/16 +( (int)y/16 *34)]==2) map_num = 2;

    if (state == "Walking")
    {
        
        if (facingDirection == "Down")
        {
            if (y >= b + 16){
                state = "Stop";
                counterWalk = 1;
            }
            else{
                (spritePlayer).move(0, playerMovementSpeed);
                (spritePlayer).setTextureRect(sf::IntRect(counterWalk * 64,0,sheetRect,sheetRect));
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
            }
            else{
                (spritePlayer).move(0, -playerMovementSpeed);
                (spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,3*sheetRect,sheetRect,sheetRect));
                view.move(0, -playerMovementSpeed);
                     
                counterWalk++;
                if(counterWalk == sizeAnim){
                    counterWalk = 0;
                 }
            }
        }
        
        if (facingDirection == "Right")
        {
            if (x >= a + 16){ // -10 because of initial position
                state = "Stop";
                counterWalk = 1;
            }
            else{
                (spritePlayer).move(playerMovementSpeed, 0);
                (spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,2*sheetRect,sheetRect,sheetRect));
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
            }
            else{
                (spritePlayer).move(-playerMovementSpeed, 0);
                (spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,sheetRect,sheetRect,sheetRect));
                view.move(-playerMovementSpeed, 0);
                
                counterWalk++;
                if(counterWalk == sizeAnim){
                    counterWalk = 0;
                }
            }
        }

    }
   
    if (state == "Stop"){
    
        if (event.type == sf::Event::KeyPressed){
                
            if (event.key.code == sf::Keyboard::Left) {
                if (facingDirection != "Left"){
                    (spritePlayer).setTextureRect(sf::IntRect(0,sheetRect,sheetRect,sheetRect));
                    facingDirection = "Left";
                    counterWalk = 1;
                }
                else{
                    if(collision[(int) x/16 -1+( (int)y/16 *34)] <6 && x > 10){ //&& x>0
                        facingDirection = "Left";
                        state = "Walking";
                        a = x;
                        b = y;
                    }
                }
            }
        
            if (event.key.code == sf::Keyboard::Right) {
                if (facingDirection != "Right"){
                    (spritePlayer).setTextureRect(sf::IntRect(0,2*sheetRect,sheetRect,sheetRect));
                    facingDirection = "Right";
                    counterWalk = 1;
                }
                else{
                    if(collision[(int) x/16 +1+( (int) y/16 *34)]<6 && x<528){ //&& x<33
                        facingDirection = "Right";
                        state = "Walking";
                        a = x;
                        b = y;
                    }
                }
            }
        
            if (event.key.code == sf::Keyboard::Up) {
                if (facingDirection != "Up"){
                    (spritePlayer).setTextureRect(sf::IntRect(0,3*sheetRect,sheetRect,sheetRect));
                    facingDirection = "Up";
                    counterWalk = 1;
                }
                else{
                    if(collision[(int) x/16 +(((int) y/16 -1)*34)]<6 && y > 10){  //&& y>0
                        facingDirection = "Up";
                        state = "Walking";
                        a = x;
                        b = y;
                    }
                }
            }
        
            if (event.key.code == sf::Keyboard::Down) {
                if (facingDirection != "Down"){
                    (spritePlayer).setTextureRect(sf::IntRect(0,0,sheetRect,sheetRect));
                    facingDirection = "Down";
                    counterWalk = 1;
                }
                else{
                    if(collision[(int) x/16 + ((y/16 +1)*34)]<6 && y < 528){  // && y<33
                        facingDirection = "Down";
                        state = "Walking";
                        a = x;
                        b = y;
                    }
                }
            }
        
              
        }
    }
    
//    std::cout << facingDirection << std::endl;
//    std::cout << state << std::endl;
    
}
