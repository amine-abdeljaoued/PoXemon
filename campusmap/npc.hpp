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
        Npc(string name, string pathName, int sheetPosX, int sheetPosY, int sheetRectX,int sheetRectY, float scale, int posX, int posY, vector<string> discu, bool fixed, bool seller);
        void draw(sf::RenderWindow &window) const;
        void speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer);
        void speakScenario(sf::RenderWindow &window, sf::View &view, Trainer &trainer, map<string,string> &scenario);
        sf::Vector2f getPos();
        int speakCounter;
        bool seller;
        string name;

    protected:
        sf::Texture textureNpc;
        sf::Sprite spriteNpc;
        vector<string> discussion;
        sf::Font font;
        sf::Text text;
        sf::ConvexShape bubble;
        sf::FloatRect getViewBounds(const sf::View &view);
        int sheetRectX;
        int sheetRectY;
        bool fixed;
        
        
};

