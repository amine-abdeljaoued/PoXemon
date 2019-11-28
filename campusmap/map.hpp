#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include "tilemap.hpp"
#include "npc.hpp"
#include "trainer.hpp"
using namespace std;

class Map 
{
    public:
        Map(int i);
        ~Map();
        void draw(sf::RenderWindow &window, Trainer &trainer) const;
    private:
        TileMap background;
        list<Npc*> npcs;

        
};
