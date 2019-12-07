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



Map::Map(sf::RenderWindow &window, string &map_name)
{
    collision_.insert(pair<string, const int*>("first", collision));
    collision_.insert(pair<string, const int*>("second", collision2));
    
    if(map_name == "first")
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
    if(map_name == "second")
    {
        if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level2, 34, 34)){
        cout << "Error loading the sprite";
        }
    }
    
}

Map::~Map()
{
    for (vector<Npc*>::iterator it = npcs.begin(); it != npcs.end(); it++)
    {
        delete *it;
    }
}

void Map::initialisation(sf::Clock& clock, sf::RenderWindow &window, int& alpha){
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

void Map::trainerDisplacement(Trainer &trainer, sf::Event &event, sf::Clock& clock, int& alpha, string &map_name){
    
    sf::Vector2f position = trainer.spritePlayer.getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    
    //Switching map
    if (collision[(int) x/16 +( (int)y/16 *34)]==2){
        map_name = "second";
        clock.restart();
        alpha = 250;
    }
    
    
    if (trainer.state == "Stop"){
       
           if (event.type == sf::Event::KeyPressed){
                   
               if (event.key.code == sf::Keyboard::Left) {
                   if (trainer.facingDirection != "Left"){
                    (trainer.spritePlayer).setTextureRect(sf::IntRect(0,trainer.sheetRect,trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Left";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 -1+( (int)y/16 *34)] <6 && x > 10){ //&& x>0
                           trainer.facingDirection = "Left";
                           trainer.state = "Walking";
                           trainer.a = x;
                           trainer.b = y;
                       }
                   }
               }
           
               if (event.key.code == sf::Keyboard::Right) {
                   if (trainer.facingDirection != "Right"){
                       (trainer.spritePlayer).setTextureRect(sf::IntRect(0,2*trainer.sheetRect,trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Right";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 +1+( (int) y/16 *34)]<6 && x<528){ //&& x<33
                           trainer.facingDirection = "Right";
                           trainer.state = "Walking";
                           trainer.a = x;
                           trainer.b = y;
                       }
                   }
               }
           
               if (event.key.code == sf::Keyboard::Up) {
                   if (trainer.facingDirection != "Up"){
                       (trainer.spritePlayer).setTextureRect(sf::IntRect(0,3*trainer.sheetRect,trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Up";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]<6 && y > 10){  //&& y>0
                           trainer.facingDirection = "Up";
                           trainer.state = "Walking";
                           trainer.a = x;
                           trainer.b = y;
                       }
                   }
               }
           
               if (event.key.code == sf::Keyboard::Down) {
                   if (trainer.facingDirection != "Down"){
                       (trainer.spritePlayer).setTextureRect(sf::IntRect(0,0,trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Down";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 + ((y/16 +1)*34)]<6 && y < 528){  // && y<33
                           trainer.facingDirection = "Down";
                           trainer.state = "Walking";
                           trainer.a = x;
                           trainer.b = y;
                       }
                   }
               }
           
                 
           }
    }
}

void Map::draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, int& alpha, sf::Event &event, string &map_name){
    
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
    
    trainer.draw(window);
    
    if (trainer.coll_num >= 8){ //case of contact with npc
        (*(npcs[0])).speak(window, view);
    }
    initialisation(clock, window, alpha);
    
    this->trainerDisplacement(trainer,event,clock,alpha,map_name);
}
        
    
    



