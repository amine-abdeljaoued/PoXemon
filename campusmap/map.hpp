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
#include "shop.hpp"

using namespace std;

//This is our class for our map

class Map 
{
    public:
        Map(sf::RenderWindow &window);
        ~Map();
        void draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, sf::Event &event);
        void initialisation(sf::RenderWindow &window, Trainer &trainer, sf::View &view);
        void end(sf::RenderWindow &window, Trainer &trainer);
        static sf::FloatRect getViewBounds(const sf::View &view);
        void trainerDisplacement(sf::RenderWindow &window, Trainer &trainer, sf::Event &event, sf::Clock& clock, sf::View &view);
        void fillTree(sf::RenderWindow &window);
        void movingFlower(sf::RenderWindow &window, int x, int y);
        void openDoorS(sf::RenderWindow &window, Trainer &trainer);
    
    private:
        TileMap background1_1;
        TileMap background1_2;
        TileMap background2_1;
        //TileMap background2_2;
        TileMap background3_1;
        TileMap background3_2;
        TileMap background4_1;
        TileMap background4_2;
        map<string, vector<Npc*> > npcs; //Map mapping each map_name to its associated vector of npcs
        
        map<string, const int*> collision_;
        string map_name;
        int alpha;
        string state;
        int animationCounter;
        int animationDoor;
        sf::Clock animClock;
        sf::Texture texture_1; //tileset1
        sf::Texture texture_2; //tileset2
        sf::Texture texture_3; //tileset3
        sf::Texture pokeInterior;
        sf::Sprite pokeBuilding;
        Shop shop;
    
        //Places of Spawn of the Trainer
        int initialX;
        int initialY;
    
        map<string,vector<vector<int>>> spawn_dict;
        int door = 0; //which spwaning position
        vector<string> map_list;
};  
