#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Trainer {
    public:
        Trainer(float Speed, int sheetRect, int sizeAnim);
        void displacement(sf::Event &event, sf::View &view, const int* collision);
        void setSpeed(sf::Event &event);
        void draw(sf::RenderWindow &window) const;
        //sf::Clock* clock;
    private:
        
        float playerMovementSpeed;
        int sheetRect; //Size of a single character position on the sprite sheet
        int sizeAnim; //Number of animations per direction of movement
        int counterWalk = 0;
        std::string facingDirection = "Down";
        sf::Texture texturePlayer;
        sf::Sprite spritePlayer;
};
