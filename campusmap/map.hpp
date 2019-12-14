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
        void movingFlower(sf::RenderWindow &window, int x, int y);
    
    private:
        TileMap background1_1;
        TileMap background1_2;
        /* TileMap background2_1;
        TileMap background2_2; */
        vector<Npc*> npcs;
        map<string, const int*> collision_;
        string map_name;
        int alpha;
        string state;
        int animationCounter;
        sf::Clock animClock;
        sf::Texture texture_1; //tileset1
        sf::Texture texture_2; //tileset2
        sf::Texture texture_3; //tileset3
        //dictionnary of map names and the collision map associated to it, initiaised in the constructor.
};  
