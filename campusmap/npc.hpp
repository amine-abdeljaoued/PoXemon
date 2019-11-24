#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>


class Npc{
    public:
        Npc();
        void draw(sf::RenderWindow &window) const;

    private:
        sf::Texture textureNpc;
        sf::Sprite spriteNpc;
};