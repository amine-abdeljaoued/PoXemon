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
        void draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, sf::Event &event, string &map_name);
        void initialisation(sf::RenderWindow &window, Trainer &trainer);
        void end(sf::RenderWindow &window, Trainer &trainer);
        static sf::FloatRect getViewBounds(const sf::View &view);
        void trainerDisplacement(sf::RenderWindow &window, Trainer &trainer, sf::Event &event, sf::Clock& clock, string &map_name, sf::View &view);
        void fillTree(sf::RenderWindow &window);
    
    private:
        TileMap background;
        vector<Npc*> npcs;
        map<string, const int*> collision_;
        string map_name;
        int alpha;
        string state;
        //dictionnary of map names and the collision map associated to it, initiaised in the constructor.
};  
