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
#include <random>

using namespace std;



Map::Map(sf::RenderWindow &window, string &map_name)
{
    alpha = 255;
    state = "start";
    collision_.insert(pair<string, const int*>("first", collision));
    collision_.insert(pair<string, const int*>("second", collision2));
    
    this->map_name= map_name;    
    vector<string> dialogue1;
    dialogue1.push_back("Welcome on our campus!");
    dialogue1.push_back("Start by exploring"); /*
    string dialogue1 [2] = {"Welcome on our campus!","Start by exploring"}; */
    Npc* toto = new  Npc("Sprites/NPC2.png",70,50,0.5f,200,212,dialogue1);
    npcs.push_back(toto) ;
    
}

Map::~Map()
{
    
    for (vector<Npc*>::iterator it = npcs.begin(); it != npcs.end(); it++)
    {
        delete *it;
    }
}

void Map::initialisation(sf::RenderWindow &window){

    sf::ConvexShape black;
    black.setPointCount(4);
    black.setPoint(0, sf::Vector2f(-256, -256));
    black.setPoint(1, sf::Vector2f(800, -256));
    black.setPoint(2, sf::Vector2f(800, 800));
    black.setPoint(3, sf::Vector2f(-256, 800));

    black.setFillColor(sf::Color(10, 10, 10, alpha));
    window.draw(black);
    alpha -= 15;
    std::cout << alpha << std::endl;
    
}

void Map::end(sf::RenderWindow &window){
    sf::ConvexShape black;
    black.setPointCount(4);
    black.setPoint(0, sf::Vector2f(-256, -256));
    black.setPoint(1, sf::Vector2f(800, -256));
    black.setPoint(2, sf::Vector2f(800, 800));
    black.setPoint(3, sf::Vector2f(-256, 800));
    black.setFillColor(sf::Color(10, 10, 10, alpha));
    window.draw(black);
    alpha += 15;
    std::cout << alpha << std::endl;
    
}


void Map::trainerDisplacement(sf::RenderWindow &window, Trainer &trainer, sf::Event &event, sf::Clock& clock, int& alpha, string &map_name){
    
    sf::Vector2f position = trainer.spritePlayer.getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    
    //Switching map
    if (collision[(int) x/16 +( (int)y/16 *34)]==2){
        if (alpha < 255 && state == "end"){
            end(window);
        }
        else{
            map_name = "second";
            clock.restart();
            state = "start";
        }
            
    }
    
    if (trainer.state == "Walking"){
        if (collision[(int) x/16 +( (int)y/16 *34)]==1){
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            float probagenerated = dis(gen);
            if (probagenerated<0.02) std::cout<<"POKEEEEMMMOONNN"<<std::endl;
            
            sf::Texture texture;
            texture.loadFromFile("Sprites/tileset3.png");
            sf::Sprite sprite;
            (sprite).setTexture(texture);
            (sprite).setTextureRect(sf::IntRect(197, 144, 16, 16));
            int a = (int) x/16;
            int b = (int) y/16;
            sprite.setPosition(16 * a , 16 * b);
            window.draw(sprite);
        }
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
                       else{
                           trainer.state = "Stop";
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
                       else{
                           trainer.state = "Stop";
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
                       else{
                           trainer.state = "Stop";
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
                       if(collision_[map_name][(int) x/16 + ((y/16 +1)*34)]<6 && y < 512){  // && y<32
                           trainer.facingDirection = "Down";
                           trainer.state = "Walking";
                           trainer.a = x;
                           trainer.b = y;
                       }
                       else{
                           trainer.state = "Stop";
                       }
                   }
               }
           
                 
           }
    }
}

void Map::draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, sf::Event &event, string &map_name){
    
    std::cout << state << std::endl;
    
    fillTree(window);
    
    if(map_name == "first")
    {
        if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 33)){
            cout << "Error loading the sprite";
        }
    }
    
    if(map_name == "second")
       {
           if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level2, 34, 33)){
           cout << "Error loading the sprite";
           }
       }
    
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
    if(npcs.size() == 0){
        trainer.draw(window);
    }
    
    if (trainer.coll_num >= 8){ //case of contact with npc
        (*(npcs[0])).speak(window, view);
    }
    
    if (alpha > 0 && state == "start"){
        initialisation(window);
    }
    else{
        state = "end";
    }
    
    this->trainerDisplacement(window, trainer,event,clock,alpha,map_name);
}
        
    
void Map::fillTree(sf::RenderWindow &window){
    sf::Texture texture;
    texture.loadFromFile("Sprites/tileset1.png");
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    sf::Sprite sprite;
                    (sprite).setTexture(texture);
                    (sprite).setTextureRect(sf::IntRect(273 + k * 17, 290 + l*17, 16, 16));
                    sprite.setPosition(-160 + k * 16 + i * 32, -176 + l * 16 + j * 32);
                    window.draw(sprite);
                }
            }
        }
    }
    
    //Top
    for(int i = 0; i < 17; i++){
        for(int k = 0; k < 2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 324, 16, 16));
            sprite.setPosition(0 + k * 16 + i * 32, -16);
            window.draw(sprite);
        }
    }
    
    //Bottom
    for(int i = 0; i < 17; i++){
        for(int k = 0; k < 2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 291, 16, 16));
            sprite.setPosition(0 + k * 16 + i * 32, 528);
            window.draw(sprite);
        }
    }
}


