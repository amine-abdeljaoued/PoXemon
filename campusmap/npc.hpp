#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
using namespace std;

class Npc {
    public:
        Npc(string pathName, int sheetRectX,int sheetRectY, float scale, int posX, int posY, vector<string> discu);
        void draw(sf::RenderWindow &window) const;
        void speak(sf::RenderWindow &window, sf::View &view);
        sf::Vector2f getPos();

    private:
        sf::Texture textureNpc;
        sf::Sprite spriteNpc;
        vector<string> discussion;
        int speakCounter;
        sf::Font font;
        sf::Text text;
        sf::RectangleShape bubble;
        sf::FloatRect getViewBounds(const sf::View &view);
};