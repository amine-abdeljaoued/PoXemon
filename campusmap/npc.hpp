#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "trainer.hpp"
using namespace std;

class Npc {
    public:
        Npc(string pathName, int sheetPosX, int sheetPosY, int sheetRectX,int sheetRectY, float scale, int posX, int posY, vector<string> discu);
        void draw(sf::RenderWindow &window) const;
        void speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer);
        sf::Vector2f getPos();
        int speakCounter;

    private:
        sf::Texture textureNpc;
        sf::Sprite spriteNpc;
        vector<string> discussion;
        sf::Font font;
        sf::Text text;
        sf::ConvexShape bubble;
        sf::FloatRect getViewBounds(const sf::View &view);
        int sheetRectX;
        int sheetRectY;
};
