#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>


class Trainer {
    public:
        Trainer(sf::Sprite *sprite, float Speed, int sheetRect, int sizeAnim);
        void displacement(sf::Event &event, sf::View &view);
        
        sf::Sprite *spritePlayer; // With texture already loaded

    private:
        
        float playerMovementSpeed;
        int sheetRect; //Size of a single character position on the sprite sheet
        int sizeAnim; //Number of animations per direction of movement
        int counterWalk = 0;
        

};