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
    //Part 1: Defining all the tilemaps
    background1_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 33);
    background1_2.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level2, 34, 33);
    background2_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level3, 34, 33);
    background3_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level4, 34, 33);
    background3_2.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level4_2, 34, 33);
    background4_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level5, 34, 33);
    background4_2.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level5_2, 34, 33);
    background7_1.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level7_1, 34, 33);
    background7_2.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level7_2, 34, 33);
    
    
    alpha = 255;
    state = "start";
    door = 0;
    enter = false;
    
    //Part 2: Creation of the collision maps
    collision_.insert(pair<string, const int*>("first", collision));
    collision_.insert(pair<string, const int*>("second", collision2));
    collision_.insert(pair<string, const int*>("third", collision3));
    collision_.insert(pair<string, const int*>("pokeShop", pokeShopC));
    collision_.insert(pair<string, const int*>("fourth", collision4));
    collision_.insert(pair<string, const int*>("pokeCenter", pokeCenterC));
    collision_.insert(pair<string, const int*>("home", collision7));
    
    map_name= "first"; //Beggining of the game
    
    //Part 3: Creation of the NPCs
    
    //For the first_map 
    vector<Npc*> npcs_map1;
    
    vector<string> disp;
    disp.push_back("Here you can catch water pokemons");
    disp.push_back("Press x near the lake to fish");
    Npc* pannel1 = new Npc(288,188,disp);
    npcs_map1.push_back(pannel1);
    
    vector<string> dialogue1;
    dialogue1.push_back("Welcome on our campus!");
    dialogue1.push_back("Start by exploring");
    npcs_map1.push_back(new  Npc("toto", "Sprites/NPC1.png",145,97,32,32,1.f,200,240,dialogue1, false));
    
    npcs_map1.push_back(new Npc("bob","Sprites/NPC1.png",113,97,32,32,1.f,264,240,{"dialogue"}, false));
    
    npcs_map1.push_back(new Npc("nerd","Sprites/NPC1.png",17,97,32,32,1.f,136,240,{"Hi"}, false));

    npcs.insert(pair< string, vector<Npc*> >("first", npcs_map1));
    
    //For the underground
    vector<Npc*> npcs_underground;
    
    vector<string> info_underground;
    info_underground.push_back("Hello, welcome to our underground");
    info_underground.push_back("Try to find the exit...");
    Npc* pannel_udg = new Npc(95,372,info_underground);
    npcs_underground.push_back(pannel_udg);
    
    
    vector<string> dialogue_under;
    dialogue_under.push_back("Look at the nice fountain");
    dialogue_under.push_back("There is no exit here");
    dialogue_under.push_back("You just lost 2 minutes of your time");
    Npc* digger = new Npc("digger","Sprites/NPC1.png",209,673,32,32,1.f,8,16,dialogue_under,true);
    npcs_underground.push_back(digger);


    
 

    npcs.insert(pair<string, vector<Npc*> >("second", npcs_underground));

    //For the PokeShop
    vector<Npc*> npcs_pokeShop;
    vector<string> dialogueS;
    dialogueS.push_back("Welcome to our store!");
    dialogueS.push_back("What would you like to buy?");
    dialogueS.push_back("Shopping");
    Npc* seller = new  Npc("seller","Sprites/NPC1.png",497,1026,-32,32,1.f,136,96,dialogueS, true);
    npcs_pokeShop.push_back(seller) ;
    npcs.insert(pair< string, vector<Npc*> >("pokeShop", npcs_pokeShop));
    
    //For the PokeCenter
    vector<Npc*> npcs_pokeCenter;
    vector<string> dialogueC;
    dialogueC.push_back("Welcome to our center!");
    dialogueC.push_back("We restore your tired Pokemon to full health");
    dialogueC.push_back("Would you restore your Pokemon?");
    Npc* healer = new Npc("healer","Sprites/NPC1.png",433,962,32,32,1.f,105,16,dialogueC, true);
    npcs_pokeCenter.push_back(healer) ;
    npcs.insert(pair< string, vector<Npc*> >("pokeCenter", npcs_pokeCenter));
    
    //Part 4: Loading of the textures
    
    
    //Loading of the textures
    texture_1.loadFromFile("Sprites/tileset1.png");
    texture_2.loadFromFile("Sprites/tileset2.png");
    texture_3.loadFromFile("Sprites/tileset3.png");
    pokeInterior.loadFromFile("Sprites/PokeInterior.png");
    pokeBuilding.setTexture(pokeInterior);
    animationCounter = 0;
    animationDoor = 0;
    
    //Spawning position
    map_list = {"first","second","third","fourth","pokeShop","pokeCenter","home"};
    //first map
    spawn_dict.insert(pair< string, vector<vector<int> >>("first",{{264, 256},{488, 464},{184, 160}}));
    //underground
    spawn_dict.insert(pair< string, vector<vector<int> >>("second",{{488, 480}}));
    //Sport
    spawn_dict.insert(pair< string, vector<vector<int> >>("third",{{168, 464}}));
    //demi-lune
    spawn_dict.insert(pair< string, vector<vector<int> >>("fourth",{{184, 176},{360,400},{504,448}})); //376 416
    //pokeShop
    spawn_dict.insert(pair< string, vector<vector<int> >>("pokeShop",{{184, 160}}));
    //pokeCenter
    spawn_dict.insert(pair< string, vector<vector<int> >>("pokeCenter",{{104,112}}));
    
    spawn_dict.insert(pair< string, vector<vector<int> >>("home",{{8,192}}));
    
    //Scenario
    scenario.insert(pair<string, vector<string>> ("bob", {"Nice Day!","You should go to the shop to buy what you need."}));
    scenario.insert(pair<string, vector<string>> ("seller", {"Welcome to my Shop", "My name is Ms. Linz.", "Here you can buy everything that you will need to pass the test.", "But be carefull, everything has a price!", "Shopping"}));


    scenario.insert(pair<string, vector<string>> ("toto", {"Oups"}));
     
}

Map::~Map()
{
    //Delete all the Npcs from each vector of our map npc
    for (map<string, vector<Npc*> >::iterator it = npcs.begin(); it != npcs.end(); it++)
    {
        vector<Npc*> k = it->second;
        for( vector<Npc*>::iterator it1 = k.begin(); it1 != k.end(); it1++)
        {
            delete *it1;
        }
            
    }
}

void Map::initialisation(sf::RenderWindow &window, Trainer &trainer, sf::View &view){
    sf::Vector2f position = trainer.spritePlayer.getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    trainer.spritePlayer.setPosition(spawn_dict[map_name][door][0], spawn_dict[map_name][door][1]);
    view.setCenter(spawn_dict[map_name][door][0] + 16, spawn_dict[map_name][door][1] + 16);;
    trainer.state = "Blocked";
    trainer.counterWalk = 0;
    sf::ConvexShape black;
    black.setPointCount(4);
    black.setPoint(0, sf::Vector2f(-256, -256));
    black.setPoint(1, sf::Vector2f(800, -256));
    black.setPoint(2, sf::Vector2f(800, 800));
    black.setPoint(3, sf::Vector2f(-256, 800));
    black.setFillColor(sf::Color(10, 10, 10, alpha));
    window.draw(black);
    alpha -= 5;
    
//    if (alpha <= 50){
//        sf::Sprite sprite;
//        (sprite).setTexture(texture_3);
//        (sprite).setTextureRect(sf::IntRect(23 + 17 * animationDoor, 232, 16, 16));
//        sprite.setPosition(192,160);
//
//        if (animClock.getElapsedTime().asMilliseconds() > 400){
//            animationDoor-=1;
//        }
//        window.draw(sprite);
//
//
//    }
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
    
    cout << x << " " << y << endl;
    
    //Switching map
    if (collision_[map_name][(int) x/16 +( (int)y/16 *34)] >= 100 && trainer.state == "Stop"){
        int n = collision_[map_name][(int) x/16 +( (int)y/16 *34)];
        if (alpha < 250 && state == "end"){
            end(window, trainer);
        }
        else{
            map_name = map_list[((int) n /100) - 1];
            door = n % 100;
            clock.restart();
            state = "start";
            initialisation(window, trainer, view);
            trainer.counterWalk = 0;
        }
    }
    
    //Opening doors
    if ((x == 200 && map_name == "first" && trainer.facingDirection == "Up" && y >= 160 && y <= 176) ||(x == 376 && map_name == "fourth" && trainer.facingDirection == "Up" && y >= 400 && y <= 416)){ // open door of the pokeShop and pokeCenter
        enter = true;
    }
    else {
        enter = false;
    }

    //Exiting Shop
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::W&&map_name == "pokeShop"&&trainer.state == "Shopping"){
        //if (trainer.state == "Shopping")
        trainer.state = "Stop";
        //else trainer.state = "Shopping";
    }

    //Entering Speaking mode with different npcs
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::D&&trainer.state != "Walking"){
        if (collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]>=60 && collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]<=69 && trainer.facingDirection=="Up"){
            nNpc = collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)] % 60;
            if(trainer.state != "Shopping"){
                if(trainer.state == "SpeakingScenario"){
                    if(scenario[npcs[map_name][nNpc]->name].size() == 1){
                        scenario.erase(npcs[map_name][nNpc]->name);
                    }
                    else{
                        scenario[npcs[map_name][nNpc]->name].erase(scenario[npcs[map_name][nNpc]->name].begin());
                    }
                                        
                    if (scenario.begin()->first == npcs[map_name][nNpc]->name){
                        trainer.state = "SpeakingScenario";
                    }
                    else{
                        trainer.state = "Stop";
                        
                    }
                }
                else if (scenario.begin()->first == npcs[map_name][nNpc]->name){
                    trainer.state = "SpeakingScenario";
                }
                else{
                    trainer.state = "Speaking";
                    npcs[map_name][nNpc]->speakCounter ++ ;
                }
            }
        }
        else if (collision_[map_name][(int) x/16 -1+((int) y/16 *34)]>=60 && collision_[map_name][(int) x/16 -1+((int) y/16 *34)]<=69 && trainer.facingDirection=="Left"){
            nNpc = collision_[map_name][(int) x/16 -1+((int) y/16 *34)] % 60;
            if(trainer.state != "Shopping"){
                if(trainer.state == "SpeakingScenario"){
                   if(scenario[npcs[map_name][nNpc]->name].size() == 1){
                        scenario.erase(npcs[map_name][nNpc]->name);
                    }
                    else{
                        scenario[npcs[map_name][nNpc]->name].erase(scenario[npcs[map_name][nNpc]->name].begin());
                    }
                    if (scenario.begin()->first == npcs[map_name][nNpc]->name){
                        trainer.state = "SpeakingScenario";
                    }
                    else{
                        trainer.state = "Stop";
                        
                    }
                }
                else if (scenario.begin()->first == npcs[map_name][nNpc]->name){
                    trainer.state = "SpeakingScenario";
                }
                else{
                    trainer.state = "Speaking";
                    npcs[map_name][nNpc]->speakCounter ++ ;
                }
            }
        }
        else if (collision_[map_name][(int) x/16 +1+((int) y/16 *34)]>=60 && collision_[map_name][(int) x/16 +1+((int) y/16 *34)]<=69 && trainer.facingDirection=="Right"){
            nNpc = collision_[map_name][(int) x/16 +1+((int) y/16 *34)] % 60;
            if(trainer.state != "Shopping"){
                if(trainer.state == "SpeakingScenario"){
                   if(scenario[npcs[map_name][nNpc]->name].size() == 1){
                        scenario.erase(npcs[map_name][nNpc]->name);
                    }
                    else{
                        scenario[npcs[map_name][nNpc]->name].erase(scenario[npcs[map_name][nNpc]->name].begin());
                    }
                    if (scenario.begin()->first == npcs[map_name][nNpc]->name){
                        trainer.state = "SpeakingScenario";
                    }
                    else{
                        trainer.state = "Stop";
                        
                    }
                }
                else if (scenario.begin()->first == npcs[map_name][nNpc]->name){
                    trainer.state = "SpeakingScenario";
                }
                else{
                    trainer.state = "Speaking";
                    npcs[map_name][nNpc]->speakCounter ++ ;
                }
            }
        }
    }
    
    //Fishing for François
    if ((collision_[map_name][(int) x/16 + 1 +( (int)y/16 *34)]==6 &&trainer.facingDirection=="Right") || (collision_[map_name][(int) x/16 -1 +( (int)y/16 *34)]==6 &&trainer.facingDirection=="Left") || (collision_[map_name][(int) x/16  + (((int) y/16 -1) *34)]==6 &&trainer.facingDirection=="Up") || (collision_[map_name][(int) x/16 +(((int) y/16 +1) *34)]==6 &&trainer.facingDirection=="Down")){
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&trainer.fish==true&&trainer.state != "Walking"){
            if (trainer.state == "Fishing"){
                trainer.state = "stopFishing";
                trainer.counterWalk = 3;
            }
            else{
                trainer.counterWalk = 0;
                trainer.state = "Fishing";
            }
            trainer.fish =false;
        }
        if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::X){
            trainer.fish = true;
        }
    }

    //Walking
    if (trainer.state == "Walking"){
        if (collision_[map_name][(int) x/16 +( (int)y/16 *34)]==1){
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            float probagenerated = dis(gen);
            if (probagenerated<0.02) std::cout<<"POKEEEEMMMOONNN"<<std::endl;
            
            if (trainer.facingDirection == "Left" || trainer.facingDirection == "Right"){
                sf::Sprite sprite;
                (sprite).setTexture(texture_3);
                (sprite).setTextureRect(sf::IntRect(197, 144, 16, 16));
                int a = (int) x/16;
                int b = (int) y/16;
                sprite.setPosition(16 * a , 16 * b);
                window.draw(sprite);
            }
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
                       if((collision_[map_name][(int) x/16 -1+( (int)y/16 *34)] >= 100 || collision_[map_name][(int) x/16 -1+( (int)y/16 *34)] < 5) && x > 10 && collision_[map_name][(int) x/16 +( (int) y/16 *34)] != 5){ //&& x>0
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
                       if((collision_[map_name][(int) x/16 +1+( (int) y/16 *34)]<5 || collision_[map_name][(int) x/16 +1+( (int) y/16 *34)] >= 100) && x<528 && collision_[map_name][(int) x/16 +( (int) y/16 *34)] != 5){ //&& x<33
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
                           if((collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]<6 || collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)] >= 100) && y > 10){  //&& y>0
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
                       if((collision_[map_name][(int) x/16 + ((y/16 +1)*34)] >= 100 || collision_[map_name][(int) x/16 + ((y/16 +1)*34)]<6) && y < 512){  // && y<32
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
        
    
    
    
    if (map_name == "first" || map_name == "fourth" || map_name == "third" || map_name == "home") fillTree(window);
     
    
    /* trainer.displacement(event, view); */
      
    sf::Vector2f pos =trainer.getPos();
    if (map_name== "first"){
        window.draw(background1_1); 
        window.draw(background1_2); //Both backgrounds associated to each tileset will have the same background
    }
    
    else if (map_name== "second"){
        window.draw(background2_1);
//        window.draw(background2_2);
    }
    
    else if (map_name== "third"){
            window.draw(background3_1);
            window.draw(background3_2);
    }
    
    else if (map_name == "pokeShop"){
        pokeBuilding.setTextureRect(sf::IntRect(307,250,176,128));
        pokeBuilding.setPosition(128, 64);
        window.draw(pokeBuilding);
    }
    
    else if (map_name == "pokeCenter"){
        pokeBuilding.setTextureRect(sf::IntRect(42,49,224,144));
        pokeBuilding.setPosition(0, 0);
        window.draw(pokeBuilding);
    }
    
    else if(map_name== "fourth"){
        window.draw(background4_1);
        window.draw(background4_2);
    }
    
    else if(map_name== "home"){
        window.draw(background7_1);
        window.draw(background7_2);
    }
    
    openDoorS(window);
    closeDoorS(window);
    /* movingFlower(window, 176, 176); */

    for (auto const& np : npcs[map_name]) {
        sf::Vector2f pos2 = (*np).getPos();
         if(pos.y >= pos2.y)
         {
              if (trainer.state == "Speaking"){
                if((*np).name=="seller" || (*np).name=="healer"){
                    if((abs(pos.y - pos2.y) <= 32) && (abs(pos.x - pos2.x) <= 32) ){
                        (*np).speak(window, view, trainer);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
                else{
                    if((abs(pos.y - pos2.y) <= 16) && (abs(pos.x - pos2.x) <= 16) ){
                        (*np).speak(window, view, trainer);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
            }
             
            else if (trainer.state == "SpeakingScenario"){
                if((*np).name=="seller" || (*np).name=="healer"){
                    if((abs(pos.y - pos2.y) <= 32) && (abs(pos.x - pos2.x) <= 32) ){
                        (*np).speakScenario(window, view, trainer, scenario);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
                else{
                    if((abs(pos.y - pos2.y) <= 16) && (abs(pos.x - pos2.x) <= 16) ){
                        (*np).speakScenario(window, view, trainer, scenario);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
                
            }
            else {
            (*np).draw(window);
            }
         }
    }
    
    trainer.draw(window, event, view);
    
    
    for (auto const& np : npcs[map_name]) {
        sf::Vector2f pos2 = (*np).getPos();
         if(pos.y < pos2.y)
         {
              if (trainer.state == "Speaking"){
                if((*np).name=="seller" || (*np).name=="healer"){
                    if((abs(pos.y - pos2.y) <= 32) && (abs(pos.x - pos2.x) <= 32) ){
                        (*np).speak(window, view, trainer);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
                else{
                    if((abs(pos.y - pos2.y) <= 16) && (abs(pos.x - pos2.x) <= 16) ){
                        (*np).speak(window, view, trainer);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
            }
            
            else if (trainer.state == "SpeakingScenario"){
                if((*np).name=="seller" || (*np).name=="healer"){
                    if((abs(pos.y - pos2.y) <= 32) && (abs(pos.x - pos2.x) <= 32) ){
                        (*np).speakScenario(window, view, trainer, scenario);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
                else{
                    if((abs(pos.y - pos2.y) <= 16) && (abs(pos.x - pos2.x) <= 16) ){
                        (*np).speakScenario(window, view, trainer, scenario);
                    }
                    else{
                        (*np).draw(window);
                    }
                }
                 
            }
            else {
            (*np).draw(window);
            }
         }
    }
    
   //draw the walls above the door to create the illusion of "entering"
    illuCenter(window);
    illuShop(window);
    illuTunnelR(window);
    illuTunnelL(window);
    
    
    if (map_name == "fourth") tunnel(window, 544, 416);
    if (map_name == "home") tunnel(window, -128, 160);
    
    
    
    if (alpha > 0 && state == "start"){
        initialisation(window, trainer, view);
    }
    else{
        if (trainer.state == "Blocked"){
            trainer.state = "Stop";
        }
        state = "end";
    }
    this->trainerDisplacement(window, trainer,event,clock,view);
    shop.draw(window, view, event, trainer);
    
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
            (sprite).setTexture(texture_1);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 324, 16, 16));
            sprite.setPosition(0 + k * 16 + i * 32, -16);
            window.draw(sprite);
        }
    }
    
    //Bottom
    for(int i = 0; i < 17; i++){
        for(int k = 0; k < 2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_1);
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

void Map::openDoorS(sf::RenderWindow &window){
    int a;
    int b;
    if (map_name == "first"){
        a = 192;
        b = 160;
    }
    else if (map_name == "fourth"){
        a = 368;
        b = 400;
    }
    if (enter == true){
        sf::Sprite sprite;
        (sprite).setTexture(texture_3);
        (sprite).setTextureRect(sf::IntRect(23 + 17 * animationDoor, 232, 16, 16));
        sprite.setPosition(a,b);
            
        if (animClock.getElapsedTime().asMilliseconds() > 400){
            if (animationDoor < 2){
                animationDoor++;
            }
        }
        window.draw(sprite);
    }
}

void Map::closeDoorS(sf::RenderWindow &window){
    if (enter == false && animationDoor > 0){
        sf::Sprite sprite;
        (sprite).setTexture(texture_3);
        (sprite).setTextureRect(sf::IntRect(23 + 17 * animationDoor, 232, 16, 16));
        sprite.setPosition(192,160);
                
        if (animClock.getElapsedTime().asMilliseconds() > 400){
            animationDoor-=1;
        }
        window.draw(sprite);
        
    }
}

void Map::tunnel(sf::RenderWindow &window, int x, int y){
    
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 5; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(426, 18 + 17 * k, 16, 16));
            sprite.setPosition(x + i*16, y + 16 * k );
            window.draw(sprite);
        }
    }
    
    //Top
    for(int i = 0; i < 4; i++){
        for(int k = 0; k < 2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_1);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 324, 16, 16));
            sprite.setPosition(x + k * 16 + i * 32, y-16);
            window.draw(sprite);
        }
    }
    
    //Bottom
    for(int i = 0; i < 4; i++){
        for(int k = 0; k < 2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_1);
            (sprite).setTextureRect(sf::IntRect(239 + k * 17, 291, 16, 16));
            sprite.setPosition(x + k * 16 + i * 32, y+80);
            window.draw(sprite);
        }
    }
}

void Map::illuCenter(sf::RenderWindow &window){
    if (map_name == "fourth"){
        for(int i = 0; i < 3; i++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(103 + 17 * i, 52, 16, 16));
            sprite.setPosition(352 + i * 16, 384);
            window.draw(sprite);
        }
    }
}

void Map::illuShop(sf::RenderWindow &window){
    if (map_name == "first"){
        for(int i = 0; i < 3; i++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(18 + 17 * i, 52, 16, 16));
            sprite.setPosition(176 + i * 16, 144);
            window.draw(sprite);
        }
    }
}

void Map::illuTunnelR(sf::RenderWindow &window){
    if (map_name == "fourth"){
        for(int i = 0; i < 5; i++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(409, 18 + 17 * i, 16, 16));
            sprite.setPosition(528, 416 + 16 * i );
            window.draw(sprite);
            
            sf::Sprite sprite2;
            (sprite2).setTexture(texture_2);
            (sprite2).setTextureRect(sf::IntRect(426, 18 + 17 * i, 16, 16));
            sprite2.setPosition(544, 416 + 16 * i );
            window.draw(sprite2);
        }
        
        for(int k = 0; k<2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(392, 35 + 17 * k, 16, 16));
            sprite.setPosition(512, 432 + 16 * k );
            window.draw(sprite);
        }
    }
}


void Map::illuTunnelL(sf::RenderWindow &window){
    if (map_name == "home"){
        for(int i = 0; i < 5; i++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(494, 18 + 17 * i, 16, 16));
            sprite.setPosition(0, 160 + 16 * i );
            window.draw(sprite);
            
            sf::Sprite sprite2;
            (sprite2).setTexture(texture_2);
            (sprite2).setTextureRect(sf::IntRect(426, 18 + 17 * i, 16, 16));
            sprite2.setPosition(-16, 160 + 16 * i );
            window.draw(sprite2);
        }
        
        for(int k = 0; k<2; k++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(511, 35 + 17 * k, 16, 16));
            sprite.setPosition(16, 176 + 16 * k );
            window.draw(sprite);
        }
    }
}

