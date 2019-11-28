#include "map.hpp"
#include "const.hpp"
#include "trainer.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

Map::Map(int i)
{
    if(i==0)
    {
        if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 34)){
            cout << "Error loading the sprite";
        }
       
        Npc* toto = new  Npc("Sprites/NPC2.png",70,50,0.5f,200,212);
        npcs.push_back(toto) ;
    }
    if(i==2)
    {
        if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level2, 34, 34)){
            cout << "Error loading the sprite";
        }
        Npc* toto = new  Npc("Sprites/NPC2.png",70,50,0.5f,200,212);
        npcs.push_back(toto) ;
    }
    
}

Map::~Map()
{
    for (list<Npc*>::iterator it = npcs.begin(); it != npcs.end(); it++)
    {
        delete *it;
    }
}

void Map::draw(sf::RenderWindow &window, Trainer &trainer) const {
    
    sf::Vector2f pos =trainer.getPos();
    window.draw(background);
    for (auto const& np : npcs) 
    {
        sf::Vector2f pos2 = (*np).getPos(); //Here we study the respective positions of the character and the npcs 
                                            //to check in which order we draw them
        if(pos.y> pos2.y){
            (*np).draw(window);
            trainer.draw(window);
        }
        else{
            trainer.draw(window);
            (*np).draw(window);
        }
        
    } 
    
}
