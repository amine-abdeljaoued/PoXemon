#include "map.hpp"
#include "const.hpp"
#include "trainer.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;



Map::Map(int i, sf::RenderWindow &window)
{
    if(i==0)
    {
        if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 34)){
            cout << "Error loading the sprite";
        }
       
        vector<string> dialogue1;
        dialogue1.push_back("Welcome on our campus!");
        dialogue1.push_back("Start by exploring"); /* 
        string dialogue1 [2] = {"Welcome on our campus!","Start by exploring"}; */
        Npc* toto = new  Npc("Sprites/NPC2.png",70,50,0.5f,200,212,dialogue1);
        npcs.push_back(toto) ;
    }
    /* if(i==2)
    {
        ... other map
    } */
    
}

Map::~Map()
{
    for (vector<Npc*>::iterator it = npcs.begin(); it != npcs.end(); it++)
    {
        delete *it;
    }
}

void Map::initialisation(sf::Clock& clock, sf::RenderWindow &window, int& alpha) const{
//    std::cout << clock.getElapsedTime().asSeconds() << std::endl;
//    std::cout << alpha << std::endl;
    
    sf::ConvexShape black;
    black.setPointCount(4);
    black.setPoint(0, sf::Vector2f(0, 0));
    black.setPoint(1, sf::Vector2f(544, 0));
    black.setPoint(2, sf::Vector2f(544, 544));
    black.setPoint(3, sf::Vector2f(0, 544));

    if (clock.getElapsedTime().asSeconds() < 2  && alpha>200 ) {
        black.setFillColor(sf::Color(10, 10, 10, alpha));
        window.draw(black);
        if (0.05 < clock.getElapsedTime().asSeconds() && alpha >= 5) alpha = alpha - 5;
        }
}


void Map::draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, int& alpha) const {
    
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
        if (trainer.coll_num >= 8){ //case of contact with npc
            
            (*(npcs[0])).speak(window, view); 
        }

        initialisation(clock, window, alpha);

}
        
    
    



