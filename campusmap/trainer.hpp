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
        void displacement(sf::Event &event, sf::View &view, const std::string* case_num);
        void setSpeed(sf::Event &event);
        void draw(sf::RenderWindow &window) const;
        sf::Vector2f getPos();
        sf::Clock intern_clock;
        float playerMovementSpeed;
        int sheetRect; //Size of a single character position on the sprite sheet
        int sizeAnim; //Number of animations per direction of movement
        int counterWalk = 1;
        std::string facingDirection = "Down";
        sf::Texture texturePlayer;
        sf::Sprite spritePlayer;
        std::string state = "Stop";
        int a;
        int b;
        bool switchSpeak;
    
    private:
        
        
};
