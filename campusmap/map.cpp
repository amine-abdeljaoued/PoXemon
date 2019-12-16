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



Map::Map(sf::RenderWindow &window)
{
    //Defining all the maps
    background1_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 33);
    background1_2.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level2, 34, 33);
    background2_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level3, 34, 33);
//    background1_1.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level4, 34, 33));
    
    
    alpha = 255;
    state = "start";
    collision_.insert(pair<string, const int*>("first", collision));
    collision_.insert(pair<string, const int*>("second", collision2));
    collision_.insert(pair<string, const int*>("pokeShop", poke));
    
    map_name= "first";
    vector<string> dialogue1;
    dialogue1.push_back("Welcome on our campus!");
    dialogue1.push_back("Start by exploring"); /*
    string dialogue1 [2] = {"Welcome on our campus!","Start by exploring"}; */
    Npc* toto = new  Npc("Sprites/NPC2.png",70,50,0.5f,200,212,dialogue1);
    npcs.push_back(toto) ;
    
    texture_1.loadFromFile("Sprites/tileset1.png");
    texture_2.loadFromFile("Sprites/tileset2.png");
    texture_3.loadFromFile("Sprites/tileset3.png");
    pokeInterior.loadFromFile("Sprites/PokeInterior.png");
    pokeBuilding.setTexture(pokeInterior);
    animationCounter = 0;
    animationDoor = 0;
}

Map::~Map()
{
    
    for (vector<Npc*>::iterator it = npcs.begin(); it != npcs.end(); it++)
    {
        delete *it;
    }
}

void Map::initialisation(sf::RenderWindow &window, Trainer &trainer){
    trainer.state = "Blocked";
    sf::ConvexShape black;
    black.setPointCount(4);
    black.setPoint(0, sf::Vector2f(-256, -256));
    black.setPoint(1, sf::Vector2f(800, -256));
    black.setPoint(2, sf::Vector2f(800, 800));
    black.setPoint(3, sf::Vector2f(-256, 800));
    black.setFillColor(sf::Color(10, 10, 10, alpha));
    window.draw(black);
    alpha -= 5;
    
}

void Map::end(sf::RenderWindow &window, Trainer &trainer){
    trainer.state = "Blocked";
    sf::ConvexShape black;
    black.setPointCount(4);
    black.setPoint(0, sf::Vector2f(-256, -256));
    black.setPoint(1, sf::Vector2f(800, -256));
    black.setPoint(2, sf::Vector2f(800, 800));
    black.setPoint(3, sf::Vector2f(-256, 800));
    black.setFillColor(sf::Color(10, 10, 10, alpha));
    window.draw(black);
    alpha += 5;

}


void Map::trainerDisplacement(sf::RenderWindow &window, Trainer &trainer, sf::Event &event, sf::Clock& clock, sf::View &view){
    
    sf::Vector2f position = trainer.spritePlayer.getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    
    //Switching map
    if (collision_[map_name][(int) x/16 +( (int)y/16 *34)]==2){
        if (alpha < 250 && state == "end"){
            end(window, trainer);
        }
        else{
            map_name = "second";
            clock.restart();
            state = "start";
            initialisation(window, trainer);
            trainer.counterWalk = 0;
        }
    }
    
    //Fishing for François
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X){
        if ((collision_[map_name][(int) x/16 + 1 +( (int)y/16 *34)]==6 &&trainer.facingDirection=="Right") || (collision_[map_name][(int) x/16 -1 +( (int)y/16 *34)]==6 &&trainer.facingDirection=="Left") || (collision_[map_name][(int) x/16  + (((int) y/16 -1) *34)]==6 &&trainer.facingDirection=="Up") || (collision_[map_name][(int) x/16 +(((int) y/16 +1) *34)]==6 &&trainer.facingDirection=="Down")){
            if (trainer.state == "Fishing"){
                trainer.state = "stopFishing";
                trainer.counterWalk = 3;
            }
            else{
                trainer.counterWalk = 0;
                trainer.state = "Fishing";
            }
        }
    }
    
    //Entering Poke Center
    if (collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]==11 && trainer.facingDirection=="Up" && trainer.state == "Stop" && event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up){
        trainer.state = "Entering";
        if (alpha < 250 && state == "end"){
            end(window, trainer);
        }
        else{
            map_name = "pokeShop";
            clock.restart();
            state = "start";
            initialisation(window, trainer);
            trainer.counterWalk = 0;
        }
    }
    
    if ((collision_[map_name][(int) x/16 +(((int) y/16 +1)*34)]==8 && trainer.facingDirection=="Down") || (collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]==8 && trainer.facingDirection=="Up") || (collision_[map_name][(int) x/16 -1+((int) y/16 *34)]==8 && trainer.facingDirection=="Left") || (collision_[map_name][(int) x/16 +1+((int) y/16 *34)]==8 && trainer.facingDirection=="Right")){
        if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::D))){
            trainer.state = "Speaking";
            npcs[0]->speakCounter ++ ;
        }
    }
    
    
    if (trainer.state == "Walking"){
        if (collision_[map_name][(int) x/16 +( (int)y/16 *34)]==1){
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            float probagenerated = dis(gen);
            if (probagenerated<0.02) std::cout<<"POKEEEEMMMOONNN"<<std::endl;
            
            sf::Sprite sprite;
            (sprite).setTexture(texture_3);
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
                    (trainer.spritePlayer).setTextureRect(sf::IntRect(2,2+2*(trainer.sheetRect+2),trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Left";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 -1+( (int)y/16 *34)] < 5 && x > 10 && collision_[map_name][(int) x/16 +( (int) y/16 *34)] != 5){ //&& x>0
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
                       (trainer.spritePlayer).setTextureRect(sf::IntRect(2,2+3*(trainer.sheetRect+2),trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Right";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 +1+( (int) y/16 *34)]<5 && x<528 && collision_[map_name][(int) x/16 +( (int) y/16 *34)] != 5){ //&& x<33
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
                       (trainer.spritePlayer).setTextureRect(sf::IntRect(2,2 + trainer.sheetRect + 2,trainer.sheetRect,trainer.sheetRect));
                       trainer.facingDirection = "Up";
                       trainer.counterWalk = 1;
                   }
                   else{
                       if(collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]==4){
                           if (animationCounter > 0){
                               trainer.state = "Entering";
                           }
                           else{
                               //map_name = "Indoor";
                               trainer.state = "Stop";
                               end(window, trainer);
                           }
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
               }
           
               if (event.key.code == sf::Keyboard::Down) {
                   if (trainer.facingDirection != "Down"){
                       (trainer.spritePlayer).setTextureRect(sf::IntRect(2,2,trainer.sheetRect,trainer.sheetRect));
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

void Map::draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, sf::Event &event){
        
    
    
    
    if (map_name == "first") fillTree(window);
    
    /* if(map_name == "first")
    {
        if (!background.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 33)){
            cout << "Error loading the sprite";
        }
    }
    
    if(map_name == "second")
       {
           if (!background.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level2, 34, 33)){
           cout << "Error loading the sprite";
           }
       } */
    
    
    sf::Vector2f pos =trainer.getPos();
    if(map_name== "first"){
        window.draw(background1_1); 
        window.draw(background1_2); //Both backgrounds associated to each tileset will have the same background
    }
    
    if(map_name== "second"){
        window.draw(background2_1); 
//        window.draw(background2_2);
    }
    
    if (map_name == "pokeShop"){
        pokeBuilding.setTextureRect(sf::IntRect(307,250,176,128));
        pokeBuilding.setPosition(128, 64);
        window.draw(pokeBuilding);
    }
    
    movingFlower(window, 176, 176);
    openDoorS(window, trainer);

    
    for (auto const& np : npcs) 
    {
        sf::Vector2f pos2 = (*np).getPos(); //Here we study the respective positions of the character and the npcs 
                                            //to check in which order we draw them
        if(pos.y == pos2.y - 1){
            trainer.draw(window, event, view);
            (*np).draw(window);
        }
        else{
            (*np).draw(window);
            trainer.draw(window, event, view);
        }
        
    }
    
    if(npcs.size() == 0){
        trainer.draw(window, event, view);
    }
    
    if (alpha > 0 && state == "start"){
        initialisation(window, trainer);
    }
    else{
        if (trainer.state == "Blocked"){
            trainer.state = "Stop";
        }
        state = "end";
    }

   
    
    if (trainer.state == "Speaking"){
        npcs[0]->speak(window, view, trainer);
    }
    
    this->trainerDisplacement(window, trainer,event,clock,view);

}
        
    
void Map::fillTree(sf::RenderWindow &window){
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    sf::Sprite sprite;
                    (sprite).setTexture(texture_1);
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
            (sprite).setTexture(texture_3);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 324, 16, 16));
            sprite.setPosition(0 + k * 16 + i * 32, -16);
            window.draw(sprite);
        }
    }
    
    //Bottom
    for(int i = 0; i < 17; i++){
        for(int k = 0; k < 2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_3);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 291, 16, 16));
            sprite.setPosition(0 + k * 16 + i * 32, 528);
            window.draw(sprite);
        }
    }
}


void Map::movingFlower(sf::RenderWindow &window, int x, int y){
    
    sf::Sprite sprite;
    (sprite).setTexture(texture_3);
    (sprite).setTextureRect(sf::IntRect(8 + 16 * animationCounter, 44, 16, 16));
    sprite.setPosition(x, y);
    
    if (animClock.getElapsedTime().asMilliseconds() > 500){
         animationCounter++;
         if (animationCounter == 3){
             animationCounter = 0;
         }
        animClock.restart();
    }
    window.draw(sprite);
}

void Map::openDoorS(sf::RenderWindow &window, Trainer &trainer){
    if (trainer.state == "Entering"){
        sf::Sprite sprite;
        (sprite).setTexture(texture_3);
        (sprite).setTextureRect(sf::IntRect(23 + 17 * animationDoor, 232, 16, 16));
        sprite.setPosition(192,160);
        
        if (animClock.getElapsedTime().asMilliseconds() > 400){
            if (animationDoor < 2){
                animationDoor++;
            }
            else{
                trainer.state = "Stop";
                map_name = "second";
                end(window, trainer);
            }
        }
        window.draw(sprite);
    }
}
