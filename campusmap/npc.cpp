#include "npc.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
using namespace std;

Npc::Npc(string pathName, int sheetRectX,int sheetRectY, float scale , int posX, int posY) {
    if (!textureNpc.loadFromFile(/* resourcePath() + */ pathName)) {
        cout << "Error loading sprite";
    }
    (spriteNpc).setTexture(textureNpc);
    spriteNpc.setTextureRect(sf::IntRect(0,0,sheetRectX,sheetRectY));
    spriteNpc.setScale(sf::Vector2f(scale, scale));
    spriteNpc.setPosition(posX, posY);
}

void Npc::draw(sf::RenderWindow &window) const {
    window.draw(spriteNpc);
}