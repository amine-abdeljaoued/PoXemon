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
        Map(sf::RenderWindow &window, string &map_name);
        ~Map();
        void draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, int& alpha, sf::Event &event, string &map_name);
        void initialisation(sf::Clock& clock, sf::RenderWindow &window, int& alpha);
        static sf::FloatRect getViewBounds(const sf::View &view);
        void trainerDisplacement(Trainer &trainer, sf::Event &event, sf::Clock& clock, int& alpha, string &map_name);
        void fillTree(sf::RenderWindow &window);
    
    private:
        TileMap background;
        vector<Npc*> npcs;
        map<string, const int*> collision_;
        string map_name;
        //dictionnary of map names and the collision map associated to it, initiaised in the constructor.
};  
