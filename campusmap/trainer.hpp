#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "fights/Backpack.h"

using namespace std;

class Trainer {
    public:
        Trainer(float Speed, int sheetRect, int sizeAnim);
        void displacement(sf::Event &event, sf::View &view);
        void setSpeed(sf::Event &event);
        void draw(sf::RenderWindow &window, sf::Event &event, sf::View &view);
        sf::Vector2f getPos();
        sf::Clock intern_clock;
        float playerMovementSpeed;
        int sheetRect; //Size of a single character position on the sprite sheet
        int sizeAnim; //Number of animations per direction of movement
        int counterWalk = 1;
        std::string facingDirection = "Down";
        std::string state = "Stop";
        int a;
        int b;
        bool switchSpeak;
        int speedSprite;
        void fishing(sf::RenderWindow &window, sf::View &view);
        sf::Texture texturePlayer;
        sf::Sprite spritePlayer;
        sf::Font font;
        sf::Text text;
        sf::FloatRect getViewBounds(const sf::View &view);
        sf::ConvexShape bubble;
        bool fish;
    
        Backpack *opponent_bag;
        char fight_mode;
    
        //throw rock
        void rock(sf::RenderWindow &window, sf::View &view);
        int rock_throw;
    
    private:
        
        
};
