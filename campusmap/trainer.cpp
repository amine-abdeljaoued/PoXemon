#include "trainer.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <iostream>

Trainer::Trainer(sf::Sprite *sprite, float Speed, int sheetRect, int sizeAnim)
{
    spritePlayer = sprite;
    playerMovementSpeed = Speed;
    this->sheetRect = sheetRect;
    this->sizeAnim = sizeAnim;
    
}

void Trainer::displacement(sf::Event &event, sf::View &view)
{
    if (event.type == sf::Event::KeyPressed){
                sf::Vector2f position = (*spritePlayer).getPosition();
                std::cout<<(position.x+10)/16<<","<<(position.y/16)+1<<std::endl;
                
            
                if (event.key.code == sf::Keyboard::Left) {
                    (*spritePlayer).move(-playerMovementSpeed, 0);
                    (*spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,sheetRect,sheetRect,sheetRect));
                    view.move(-playerMovementSpeed, 0);
                    
                }
                if (event.key.code == sf::Keyboard::Right) {
                    (*spritePlayer).move(playerMovementSpeed, 0);
                    (*spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,2*sheetRect,sheetRect,sheetRect));
                    view.move(playerMovementSpeed, 0);
                   
                }
                if (event.key.code == sf::Keyboard::Up) {
                    (*spritePlayer).move(0, -playerMovementSpeed);
                    (*spritePlayer).setTextureRect(sf::IntRect(counterWalk * sheetRect,3*sheetRect,sheetRect,sheetRect));
                    view.move(0, -playerMovementSpeed);
                    
                }
                if (event.key.code == sf::Keyboard::Down) {
                    (*spritePlayer).move(0, playerMovementSpeed);
                    (*spritePlayer).setTextureRect(sf::IntRect(counterWalk * 64,0,sheetRect,sheetRect));
                    view.move(0,playerMovementSpeed);
                    
                }
                counterWalk++;
                if(counterWalk==sizeAnim){
                    counterWalk=0;
                }
            }
}