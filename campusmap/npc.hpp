#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Npc {
    public:
        Npc(string pathName, int sheetRectX,int sheetRectY, float scale, int posX, int posY);
        void draw(sf::RenderWindow &window) const;
        sf::Vector2f getPos();

    private:
        sf::Texture textureNpc;
        sf::Sprite spriteNpc;
};