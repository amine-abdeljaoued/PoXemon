#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include "tilemap.hpp"
#include "npc.hpp"
#include "trainer.hpp"
using namespace std;

class Map 
{
    public:
        Map(int i, sf::RenderWindow &window);
        ~Map();
        void draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, int& alpha) const;
        void initialisation(sf::Clock& clock, sf::RenderWindow &window, int& alpha) const;
        static sf::FloatRect getViewBounds(const sf::View &view);
    private:
        TileMap background;
        vector<Npc*> npcs;
};  
