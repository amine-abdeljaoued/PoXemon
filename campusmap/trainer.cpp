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

Trainer::Trainer( float Speed=16, int sheetRect=64, int sizeAnim=4)
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

    
}

void Trainer::draw(sf::RenderWindow &window) const {
    window.draw(spritePlayer);
}

void Trainer::setSpeed(sf::Event &event){
    if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift)))
    {
        playerMovementSpeed = 32;
    }
    if ((event.type == sf::Event::KeyReleased)&&((event.key.code == sf::Keyboard::LShift)||(event.key.code == sf::Keyboard::RShift)))
    {
        playerMovementSpeed = 16;
    }
}
sf::Vector2f Trainer::getPos(){
    sf::Vector2f position = (spritePlayer).getPosition();
    return position;
}

void Trainer::displacement(sf::Event &event, sf::View &view, const int* collision)
{
    setSpeed(event);
    if (event.type == sf::Event::KeyPressed){
                sf::Vector2f position = (spritePlayer).getPosition();
                int x = position.x/16+1;
                int y = position.y/16 +1;
                std::cout<<x<<","<<y<<std::endl;

            
        if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left) {
                    if (facingDirection != "Left"){
                        (spritePlayer).setTextureRect(sf::IntRect(0,sheetRect,sheetRect,sheetRect));
                        facingDirection = "Left";
                        counterWalk = 0;
                    }
                    else{
                        if(collision[x-1+(y*34)]==0 && x>0){
                            (spritePlayer).move(-playerMovementSpeed, 0);
                            (spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,sheetRect,sheetRect,sheetRect));
                            view.move(-playerMovementSpeed, 0);
                        }
                    }
                }
        }
                if (event.key.code == sf::Keyboard::Right) {
                    if (facingDirection != "Right"){
                        (spritePlayer).setTextureRect(sf::IntRect(0,2*sheetRect,sheetRect,sheetRect));
                        facingDirection = "Right";
                        counterWalk = 0;
                    }
                    else{
                        if(collision[x+1+(y*34)]==0 && x<33){
                            (spritePlayer).move(playerMovementSpeed, 0);
                            (spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,2*sheetRect,sheetRect,sheetRect));
                            view.move(playerMovementSpeed, 0);
                        }
                    }
                }
        
                if (event.key.code == sf::Keyboard::Up) {
                    if (facingDirection != "Up"){
                        (spritePlayer).setTextureRect(sf::IntRect(0,3*sheetRect,sheetRect,sheetRect));
                        facingDirection = "Up";
                        counterWalk = 0;
                    }
                    else{
                        if(collision[x+((y-1)*34)]==0 && y>0){
                            (spritePlayer).move(0, -playerMovementSpeed);
                            (spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,3*sheetRect,sheetRect,sheetRect));
                            view.move(0, -playerMovementSpeed);
                        }
                    }
                }
        
                if (event.key.code == sf::Keyboard::Down) {
                    if (facingDirection != "Down"){
                        (spritePlayer).setTextureRect(sf::IntRect(0,0,sheetRect,sheetRect));
                        facingDirection = "Down";
                        counterWalk = 0;
                    }
                    else{
                        if(collision[x+((y+1)*34)]==0 && y<33){
                            (spritePlayer).move(0, playerMovementSpeed);
                            (spritePlayer).setTextureRect(sf::IntRect(counterWalk * 64,0,sheetRect,sheetRect));
                            view.move(0,playerMovementSpeed);
                        }
                    }
                }
        
                counterWalk++;
                if(counterWalk==sizeAnim){
                    counterWalk=0;
                }
    }
}
