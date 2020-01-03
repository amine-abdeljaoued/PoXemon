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
        Npc(int posX, int posY, vector<string> discu);  //Constructors for pannels
        Npc(string name, string pathName, int sheetPosX, int sheetPosY, int sheetRectX,int sheetRectY, float scale, int posX, int posY, vector<string> discu, bool fixed);
        void draw(sf::RenderWindow &window) const;
        void speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer);
        void speakScenario(sf::RenderWindow &window, sf::View &view, Trainer &trainer, map<string,vector<string>> &scenario);
        sf::Vector2f getPos();
        int speakCounter;
        bool seller;
        string name;
        vector<string> discussion;

    protected:
        sf::Texture textureNpc;
        sf::Sprite spriteNpc;
        
        sf::Font font;
        sf::Text text;
        sf::ConvexShape bubble;
        sf::FloatRect getViewBounds(const sf::View &view);
        int sheetPosX;
        int sheetPosY;
        int sheetRectX;
        int sheetRectY;
        bool fixed;
        
};

