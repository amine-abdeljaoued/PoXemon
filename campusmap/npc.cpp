#include "npc.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
using namespace std;

Npc::Npc() {
    if (!textureNpc.loadFromFile(/* resourcePath() + */ "Sprites/NPC1.png")) {
        cout << "Error loading sprite";
    }
    (spriteNpc).setTexture(textureNpc);
    spriteNpc.setTextureRect(sf::IntRect(0,0,64,100));
    spriteNpc.setScale(sf::Vector2f(0.45f, 0.45f));
    spriteNpc.setPosition(200, 212);
}

void Npc::draw(sf::RenderWindow &window) const {
    window.draw(spriteNpc);
}