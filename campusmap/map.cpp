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
#include "fights/trainer_opponent.hpp"
#include "fights/Backpack.h"

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
    background8.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level8, 34, 33);
    background9.load("Sprites/interior.png", sf::Vector2u(16, 16), level9, 34, 33);
    background10.load("Sprites/interior.png", sf::Vector2u(16, 16), level10, 34, 33);
    background11.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level11, 34, 33);
    background11_2.load("Sprites/tileset2.png", sf::Vector2u(16, 16), level11_2, 34, 33);
    background12.load("Sprites/interior.png", sf::Vector2u(16, 16), level12, 34, 33);
    
    
    alpha = 255;
    state = "start";
    door = 0;
    enter = false;
    
    //variables for progression
    catched = false;
    water_catch = false;
    obtained_light = false;
    mr_fountain = false;
    foot_players = false;
    
    //Part 2: Creation of the collision maps
    if (catched == false) collision_.insert(pair<string, const int*>("first", collision));
    if (catched == true) collision_.insert(pair<string, const int*>("first", collision_passed));
    if (mr_fountain == false) collision_.insert(pair<string, const int*>("second", collision2));
    if (mr_fountain == true) collision_.insert(pair<string, const int*>("second", collision2_passed));
    if (foot_players == false) collision_.insert(pair<string, const int*>("third", collision3));
    if (foot_players == true) collision_.insert(pair<string, const int*>("third", collision3_passed));
    collision_.insert(pair<string, const int*>("pokeShop", pokeShopC));
    if (water_catch == false) collision_.insert(pair<string, const int*>("fourth", collision4));
    if (water_catch == true) collision_.insert(pair<string, const int*>("fourth", collision4_passed));
    collision_.insert(pair<string, const int*>("pokeCenter", pokeCenterC));
    if (obtained_light == false) collision_.insert(pair<string, const int*>("home", collision7));
    if (obtained_light == true) collision_.insert(pair<string, const int*>("home", collision7_passed));
    collision_.insert(pair<string, const int*>("maze", collision8));
    collision_.insert(pair<string, const int*>("interior_80", collision9));
    collision_.insert(pair<string, const int*>("room_clement", collision10));
    collision_.insert(pair<string, const int*>("bossfinal", collision11));
    collision_.insert(pair<string, const int*>("hall", collision12));
    
    map_name= "first"; //Beggining of the game
    
    //Part 3: Creation of the NPCs and opponent trainers
    
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
    
    vector<string> dialogue2;
    dialogue2.push_back("Before adventuring yourself");
    dialogue2.push_back("into the wild");
    dialogue2.push_back("try fighting one wild PoXemon !");
    if (catched == false) npcs_map1.push_back(new Npc("passeur","Sprites/NPC1.png",432,675,32,32,1.f,24,224,dialogue2, false));
    
    vector<string>trainer_dialogue1;
    trainer_dialogue1.push_back("You don't seem to know who I am");
    trainer_dialogue1.push_back("Fighting");
    npcs_map1.push_back(new Trainer_opponent("Fighter","Sprites/NPC1.png",113,97,32,32,1.f,264,320,trainer_dialogue1, false, 1));
    npcs.insert(pair< string, vector<Npc*> >("first", npcs_map1));
    
    //For the underground alias second
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
    dialogue_under.push_back("Now let's fight !");
//    intiate fight
//    if game is won change mr_fountain to true else do nothing
    Npc* digger = new Npc("digger","Sprites/NPC1.png",209,673,32,32,1.f,8,16,dialogue_under,true);
    npcs_underground.push_back(digger);
    
    vector<string> dialogue_pass4;
    dialogue_pass4.push_back("Have you seen the nice fountain ?");
    dialogue_pass4.push_back("It's nice isn't it ?");
    Npc* passeur4 = new Npc("passeur4","Sprites/NPC1.png",432,675,32,32,1.f,504,16,dialogue_pass4, false);
    if (mr_fountain == false) npcs_underground.push_back(passeur4);

    npcs.insert(pair<string, vector<Npc*> >("second", npcs_underground));

    //For the PokeShop
    vector<Npc*> npcs_pokeShop;
    vector<string> dialogueS;
    dialogueS.push_back("Welcome to our store!");
    dialogueS.push_back("What would you like to buy?");
    dialogueS.push_back("Shopping");
    Npc* seller = new  Npc("seller","Sprites/NPC1.png",497,1026,-32,32,1.f,136,96,dialogueS, seller);
    npcs_pokeShop.push_back(seller) ;
    npcs.insert(pair< string, vector<Npc*> >("pokeShop", npcs_pokeShop));
    
    //For the PokeCenter
    vector<Npc*> npcs_pokeCenter;
    vector<string> dialogueC;
    dialogueC.push_back("Welcome to our center!");
    dialogueC.push_back("We restore your tired Pokemon to full health");
    dialogueC.push_back("Would you restore your Pokemon?");
    dialogueC.push_back("Healing");
    Npc* healer = new Npc("healer","Sprites/NPC1.png",433,962,32,32,1.f,105,16,dialogueC, true);
    npcs_pokeCenter.push_back(healer) ;
    npcs.insert(pair< string, vector<Npc*> >("pokeCenter", npcs_pokeCenter));
    
    //For Home
    vector<Npc*> npcs_home;
    vector<string> dialogueH;
    dialogueH.push_back("Clement seems to be working...");
    dialogueH.push_back("How unusual !");
    dialogueH.push_back("Do you want to throw a rock");
    dialogueH.push_back("on his window?");
    dialogueH.push_back("Throwing");
	dialogueH.push_back("Come inside the bulding !");
    npcs_home.push_back(new Npc("clemW","Sprites/NPC1.png",17,97,1,1,1.f,248,192,dialogueH, true)) ;
    
    vector<string> dialogue_pass;
    dialogue_pass.push_back("You wouldn't want to go in there");
    dialogue_pass.push_back("without a light...");
    dialogue_pass.push_back("have you try asking Clement ?");
    dialogue_pass.push_back("you can talk to him");
    dialogue_pass.push_back("by pressing D when");
    dialogue_pass.push_back("you are in front of");
    dialogue_pass.push_back("his window, on the");
    dialogue_pass.push_back("right of the door");
    dialogue_pass.push_back("when looking the building");
    dialogue_pass.push_back("next to a big tree");
    dialogue_pass.push_back("not far from here");
    Npc* passeur3 = new Npc("passeur3","Sprites/NPC1.png",430,736,32,32,1.f,470,96,dialogue_pass,true);
    if (obtained_light == false) npcs_home.push_back(passeur3);
    
    npcs.insert(pair< string, vector<Npc*> >("home", npcs_home));
    
    //For interior_80
    vector<Npc*> npcs_80;
    vector<string> dialogue_80;
    dialogue_80.push_back("This fridge looks dirty");
    dialogue_80.push_back("Do you want to open it?");
    dialogue_80.push_back("You die because of the smell.");
    dialogue_80.push_back("Dead");
    Npc* fridge = new Npc("fridge","Sprites/NPC1.png",17,97,1,1,1.f,264,160,dialogue_80,false);
    npcs_80.push_back(fridge);

    npcs.insert(pair<string, vector<Npc*> >("interior_80", npcs_80));

    
    //For room_clement
    vector<Npc*> npcs_roomC;
    vector<string> dialogue_light;
    dialogue_light.push_back("So you want to adventure yourself");
    dialogue_light.push_back("into the cave ?");
    dialogue_light.push_back("I guess you don't have a light");
    dialogue_light.push_back("Want one ? Fight me first !");
//    intiate fight
        
//    if fight is won change obtained_light to true
    dialogue_light.push_back("Arghhhhhhhhh");
    dialogue_light.push_back("I underestimated you...");
    dialogue_light.push_back("You well deserve this");
    dialogue_light.push_back("You obtained LIGHT");
    dialogue_light.push_back("LIGHT is activiated in dark places");
    dialogue_light.push_back("also be cartefull, some say");
    dialogue_light.push_back("wild animals live in the fridge");
    dialogue_light.push_back("I wouldn't try to open it.");

    //    if fight is loss
        dialogue_light.push_back("Hahahaha you suck !");
    Npc* clement = new Npc("clement","Sprites/NPC1.png",241,673,32,32,1.f,232,256,dialogue_light,false);
    npcs_roomC.push_back(clement);

    npcs.insert(pair<string, vector<Npc*> >("room_clement", npcs_roomC));
    
        //For demi-lune alias fourth
    vector<Npc*> npcs_demilune;
    vector<string> dialogue_dl;
    dialogue_dl.push_back("Did you know that");
	dialogue_dl.push_back("You can catch PoXemon");
    dialogue_dl.push_back("By fishing or in tall grass");
    Npc* passeur2 = new Npc("passeur2","Sprites/NPC1.png",430,736,32,32,1.f,488,452,dialogue_dl,true);
    if (water_catch == false) npcs_demilune.push_back(passeur2);

    npcs.insert(pair<string, vector<Npc*> >("fourth", npcs_demilune));
    
    //For sports alias third
    vector<Npc*> npcs_sport;
    vector<string> dialogue_sp;
    dialogue_sp.push_back("You are not yet ready to fight");
    dialogue_sp.push_back("World champion PoXemon trainer");
    dialogue_sp.push_back("His name is Julien");
    dialogue_sp.push_back("But he clames he claims to be");
    dialogue_sp.push_back("the world champion of everything");
    dialogue_sp.push_back("I bet you will beat him pfff");
    dialogue_sp.push_back("But first you need some training");
    dialogue_sp.push_back("Go see the players on the field");
    dialogue_sp.push_back("They are very good");
	dialogue_sp.push_back("but don't interrupt them");
    dialogue_sp.push_back("speak to the referee");
    Npc* passeur5 = new Npc("passeur5","Sprites/NPC1.png",432,675,32,32,1.f,440,384,dialogue_sp,false);
    if (foot_players == false) npcs_sport.push_back(passeur5);

    dialogue_pl.push_back("Hi I'm the referee");
    dialogue_pl.push_back("Do you want to see");
    dialogue_pl.push_back("what my team is capable of ?");
    //initiate fight
    //if fight is won set foot_players to true
    Npc* arbitre = new Npc("arbitre","Sprites/NPC1.png",241,1561,32,32,1.f,248,128,dialogue_pl,false);
    npcs_sport.push_back(arbitre);
    
    Npc* bla = new Npc("bla","Sprites/NPC1.png",17,1625,32,32,1.f,424,144,dialogue_pl,true);
    npcs_sport.push_back(bla);
    Npc* player_foot2 = new Npc("player_foot2","Sprites/NPC1.png",17,1625,32,32,1.f,344,144,dialogue_pl,true);
    npcs_sport.push_back(player_foot2);
    Npc* player_foot3 = new Npc("player_foot3","Sprites/NPC1.png",17,1817,32,32,1.f,360,208,dialogue_pl,true);
    npcs_sport.push_back(player_foot3);
    Npc* player_foot4 = new Npc("player_foot4","Sprites/NPC1.png",17,1625,32,32,1.f,360,80,dialogue_pl,true);
    npcs_sport.push_back(player_foot4);
    Npc* player_foot5 = new Npc("player_foot5","Sprites/NPC1.png",17,1817,32,32,1.f,248,64,dialogue_pl,true);
    npcs_sport.push_back(player_foot5);
    Npc* player_foot6 = new Npc("player_foot6","Sprites/NPC1.png",17,1625,32,32,1.f,264,176,dialogue_pl,true);
    npcs_sport.push_back(player_foot6);
    Npc* player_foot7 = new Npc("player_foot7","Sprites/NPC1.png",17,1817,32,32,1.f,200,160,dialogue_pl,true);
    npcs_sport.push_back(player_foot7);
    Npc* foot_player1 = new Npc("foot_player1","Sprites/NPC1.png",433,1657,32,32,1.f,72,144,dialogue_pl,true);
    npcs_sport.push_back(foot_player1);
    Npc* foot_player2 = new Npc("foot_player2","Sprites/NPC1.png",433,1881,32,32,1.f,152,176,dialogue_pl,true);
    npcs_sport.push_back(foot_player2);
    Npc* foot_player3 = new Npc("foot_player3","Sprites/NPC1.png",433,1657,32,32,1.f,152,144,dialogue_pl,true);
    npcs_sport.push_back(foot_player3);
    Npc* foot_player4 = new Npc("foot_player4","Sprites/NPC1.png",433,1881,32,32,1.f,120,80,dialogue_pl,true);
    npcs_sport.push_back(foot_player4);
    Npc* foot_player5 = new Npc("foot_player5","Sprites/NPC1.png",433,1657,32,32,1.f,200,96,dialogue_pl,true);
    npcs_sport.push_back(foot_player5);
    Npc* foot_player6 = new Npc("foot_player6","Sprites/NPC1.png",433,1881,32,32,1.f,232,224,dialogue_pl,true);
    npcs_sport.push_back(foot_player6);
    Npc* foot_player7 = new Npc("foot_player7","Sprites/NPC1.png",433,1657,32,32,1.f,296,112,dialogue_pl,true);
    npcs_sport.push_back(foot_player7);
    
    npcs.insert(pair<string, vector<Npc*> >("third", npcs_sport));
    
    //For the maze
    vector<Npc*> npcs_maze;
    vector<string> dialogue_mz;
    dialogue_mz.push_back("Very impressive");
    dialogue_mz.push_back("to have made it that far");
    dialogue_mz.push_back("you are exceptional !");
    dialogue_mz.push_back("Take some rest,");
    dialogue_mz.push_back("heal your pokemons,");
    dialogue_mz.push_back("and good luck");
    dialogue_mz.push_back("for that final fight !");
    dialogue_mz.push_back("Do not go gentle");
    dialogue_mz.push_back("into that good night");
    dialogue_mz.push_back("Old age should burn");
    dialogue_mz.push_back("and rave at close of day");
    dialogue_mz.push_back("Rage, rage ");
    dialogue_mz.push_back("against the dying of the light.");
    Npc* gros = new Npc("gros","Sprites/NPC1.png",336,963,32,32,1.f,248,464,dialogue_mz,false);
    npcs_maze.push_back(gros);

    npcs.insert(pair<string, vector<Npc*> >("maze", npcs_maze));
    
    //Part 4: Loading of the textures
    
    
    //Loading of the textures
    texture_1.loadFromFile("Sprites/tileset1.png");
    texture_2.loadFromFile("Sprites/tileset2.png");
    texture_3.loadFromFile("Sprites/tileset3.png");
    pokeInterior.loadFromFile("Sprites/PokeInterior.png");
    pokeBuilding.setTexture(pokeInterior);
    animationCounter = 0;
    animationDoor = 0;
    
    //for x multiple of 16, +8
    //for y multiple of 16
    
    //Spawning position
    map_list = {"first","second","third","fourth","pokeShop","pokeCenter","home","maze","interior_80","room_clement","bossfinal", "hall"};
    //first map
    spawn_dict.insert(pair< string, vector<vector<int> >>("first",{{264, 256},{8, 192},{184, 160}}));
    //underground
    spawn_dict.insert(pair< string, vector<vector<int> >>("second",{{488, 480},{520,16}}));
    //Sport
    spawn_dict.insert(pair< string, vector<vector<int> >>("third",{{472, 432},{440, 384}}));
    //demi-lune
    spawn_dict.insert(pair< string, vector<vector<int> >>("fourth",{{216, 32},{360,400},{504,448}})); //376 416
    //pokeShop
    spawn_dict.insert(pair< string, vector<vector<int> >>("pokeShop",{{184, 160}}));
    //pokeCenter
    spawn_dict.insert(pair< string, vector<vector<int> >>("pokeCenter",{{104,112}}));
    //home
    spawn_dict.insert(pair< string, vector<vector<int> >>("home",{{8,192},{472,128},{216,176}}));
    //maze
    spawn_dict.insert(pair< string, vector<vector<int> >>("maze",{{248,16},{264,464}}));
    //interior_80
    spawn_dict.insert(pair< string, vector<vector<int> >>("interior_80",{{216,368},{168,192}}));
    //room_clement
    spawn_dict.insert(pair< string, vector<vector<int> >>("room_clement",{{184,336}}));
    //bossfinal
    spawn_dict.insert(pair< string, vector<vector<int> >>("bossfinal",{{248,480}}));
    //bossfinal
    spawn_dict.insert(pair< string, vector<vector<int> >>("hall",{{248,352}}));
    
    //Scenario
    scenario.insert(pair<string, vector<string>> ("bob", {"Nice Day!","You should go to the shop to buy what you need."}));
    scenario.insert(pair<string, vector<string>> ("seller", {"Welcome to my Shop", "My name is Ms. Linz.", "Here you can buy everything that you will need to pass the test.", "But be carefull, everything has a price!", "Shopping"}));


    scenario.insert(pair<string, vector<string>> ("toto", {"Oups"}));
     
    fight = false;
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
}

void Map::end(sf::RenderWindow &window, Trainer &trainer){
    if (trainer.state != "Dead") trainer.state = "Blocked";
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
   
    cout << box.box_pokemons[5] << endl;
    cout <<( box.box_pokemons[3] == NULL) << endl;
    cout <<( box.box_pokemons[9] == NULL) << endl;
    
    sf::Vector2f position = trainer.spritePlayer.getPosition();
    int x = position.x + 16;
    int y = position.y + 16;
    //Dying
    if (trainer.state == "Dead"){
        if (alpha < 250 && state == "end") end(window, trainer);
        else{
            map_name = "pokeCenter";
            door = 0;
            clock.restart();
            state = "start";
            initialisation(window, trainer, view);
            trainer.counterWalk = 0;
        }
    }
    
    else{
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
        
        //Up dating the loaction in the backpack
        if (trainer.state == "Fishing") backpack.location = "water";
        else if (collision_[map_name][(int) x/16 +( (int)y/16 *34)] <= 3) backpack.location = case_num[collision_[map_name][(int) x/16 +( (int)y/16 *34)]];
        else backpack.location = "undefined";
        
        //Opening doors
        if ((x == 200 && map_name == "first" && trainer.facingDirection == "Up" && y >= 160 && y <= 176) ||(x == 376 && map_name == "fourth" && trainer.facingDirection == "Up" && y >= 400 && y <= 416)){ // open door of the pokeShop and pokeCenter
            enter = true;
        }
        else enter = false;

        //Exiting Shop and Center
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::W&&((map_name == "pokeShop"&&trainer.state == "Shopping")||(trainer.state == "Healing"&&map_name == "pokeCenter"))){
            if(trainer.state == "Healing"&&map_name == "pokeCenter"){
                if (center.counter == 1){
                    center.counter = 0;
                    center.sw = false;
                    center.swi1 = -1;
                    center.swi2 = -1;
                    center.Selecteditem = 0;
                }
                else{
                    center.counter = 0;
                    center.sw = false;
                    center.swi1 = -1;
                    center.swi2 = -1;
                    trainer.state = "Stop";
                }
            }
            else if(trainer.state == "Shopping"&&map_name == "pokeShop"){
                trainer.state = "Stop";
            }
        }

        //Entering Speaking mode with different npcs
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::D&&trainer.state != "Walking"){
            if (collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]>=60 && collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)]<=69 && trainer.facingDirection=="Up"){
                nNpc = collision_[map_name][(int) x/16 +(((int) y/16 -1)*34)] % 60;
                if(trainer.state != "Shopping"&&trainer.state != "Healing"){
                    if(trainer.state == "SpeakingScenario"){
                        if(scenario[npcs[map_name][nNpc]->name].size() == 1) scenario.erase(npcs[map_name][nNpc]->name);
                        else scenario[npcs[map_name][nNpc]->name].erase(scenario[npcs[map_name][nNpc]->name].begin());                
                        if (scenario.begin()->first == npcs[map_name][nNpc]->name) trainer.state = "SpeakingScenario";
                        else trainer.state = "Stop";
                    }
                    else if (scenario.begin()->first == npcs[map_name][nNpc]->name) trainer.state = "SpeakingScenario";
                    else{
                        trainer.state = "Speaking";
                        npcs[map_name][nNpc]->speakCounter ++ ;
                    }
                }
            }
            else if (collision_[map_name][(int) x/16 -1+((int) y/16 *34)]>=60 && collision_[map_name][(int) x/16 -1+((int) y/16 *34)]<=69 && trainer.facingDirection=="Left"&&npcs[map_name][collision_[map_name][(int) x/16 -1+((int) y/16 *34)] % 60]->name != ""){
                nNpc = collision_[map_name][(int) x/16 -1+((int) y/16 *34)] % 60;
                if(trainer.state != "Shopping"&&trainer.state != "Healing"){
                    if(trainer.state == "SpeakingScenario"){
                        if(scenario[npcs[map_name][nNpc]->name].size() == 1) scenario.erase(npcs[map_name][nNpc]->name);
                        else scenario[npcs[map_name][nNpc]->name].erase(scenario[npcs[map_name][nNpc]->name].begin());
                        if (scenario.begin()->first == npcs[map_name][nNpc]->name) trainer.state = "SpeakingScenario";
                        else trainer.state = "Stop";
                    }
                    else if (scenario.begin()->first == npcs[map_name][nNpc]->name) trainer.state = "SpeakingScenario";
                    else{
                        trainer.state = "Speaking";
                        npcs[map_name][nNpc]->speakCounter ++ ;
                    }
                }
            }
           else if (collision_[map_name][(int) x/16 +1+((int) y/16 *34)]>=60 && collision_[map_name][(int) x/16 +1+((int) y/16 *34)]<=69 && trainer.facingDirection=="Right"&&npcs[map_name][collision_[map_name][(int) x/16 +1+((int) y/16 *34)] % 60]->name != ""){
                nNpc = collision_[map_name][(int) x/16 +1+((int) y/16 *34)] % 60;
                if(trainer.state != "Shopping"&&trainer.state != "Healing"){
                    if(trainer.state == "SpeakingScenario"){
                       if(scenario[npcs[map_name][nNpc]->name].size() == 1) scenario.erase(npcs[map_name][nNpc]->name);
                        else scenario[npcs[map_name][nNpc]->name].erase(scenario[npcs[map_name][nNpc]->name].begin());
                        if (scenario.begin()->first == npcs[map_name][nNpc]->name) trainer.state = "SpeakingScenario";
                        else trainer.state = "Stop";
                    }
                    else if (scenario.begin()->first == npcs[map_name][nNpc]->name) trainer.state = "SpeakingScenario";
                    else{
                        trainer.state = "Speaking";
                        npcs[map_name][nNpc]->speakCounter ++ ;
                    }
                }
            }
        }
        
        //Fishing for François
        if ((collision_[map_name][(int) x/16 + 1 +( (int)y/16 *34)]==7 &&trainer.facingDirection=="Right") || (collision_[map_name][(int) x/16 -1 +( (int)y/16 *34)]==7 &&trainer.facingDirection=="Left") || (collision_[map_name][(int) x/16  + (((int) y/16 -1) *34)]==7 &&trainer.facingDirection=="Up") || (collision_[map_name][(int) x/16 +(((int) y/16 +1) *34)]==7 &&trainer.facingDirection=="Down")){
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&trainer.fish==true&&trainer.state != "Walking"){
                if (trainer.state == "Fishing"){
                    water_catch = true;
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

        //Fighting
        if (trainer.state == "Stop" && fight == true){
            fight = false;
            trainer.state = "Fighting";
        }
        
        //Backapck
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::B){
            if (trainer.state == "Backpack"){
                trainer.state = "Stop";
            }
            else if (trainer.state == "Stop"){
                trainer.state = "Backpack";
            }
        }
        
        //Box
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X && center.Selecteditem == 2 && trainer.state == "Healing") {
            trainer.state = "Box";
        }
        if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::W && center.Selecteditem == 2 && trainer.state == "Box") {
            trainer.state = "Healing";
            box.selectedPokemon_right = 0;
            box.selectedPokemon_left = 0;
            box.actual_column = 0;
        }
        
        //Walking
        if (trainer.state == "Walking"){
            if (collision_[map_name][(int) x/16 +( (int)y/16 *34)]==1){
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<> dis(0.0, 1.0);
                float probagenerated = dis(gen);
                if (probagenerated<0.02) {
                    fight = true;
                    std::cout<<"POKEEEEMMMOONNN"<<std::endl;
                    trainer.fight_mode = 'w'; //Which means single pokemon in grass
                    catched = true;
                }
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
            
            
            //fight underground
            if (collision_[map_name][(int) x/16 +( (int)y/16 *34)]==2){
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            float probagenerated = dis(gen);
                if (probagenerated<0.02) {
                    fight = true;
                    std::cout<<"POKEEEEMMMOONNN"<<std::endl;
                    trainer.fight_mode = 'w'; //Which means single pokemon in grass
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
    
}

void Map::draw(sf::RenderWindow &window,sf::View &view, Trainer &trainer, sf::Clock& clock, sf::Event &event){
        
    
    
    
    if (map_name == "first" || map_name == "fourth" || map_name == "third" || map_name == "home" || map_name == "maze" || map_name == "bossfinal") fillTree(window);
     
    
    /* trainer.displacement(event, view); */
      
    sf::Vector2f pos =trainer.getPos();
    if (map_name== "first"){
        if (catched == true){
            collision_.erase("first");
            collision_.insert(pair<string, const int*>("first", collision_passed));
        }
        window.draw(background1_1); 
        window.draw(background1_2); //Both backgrounds associated to each tileset will have the same background
    }
    
    else if (map_name== "second"){
        if (mr_fountain == true){
            collision_.erase("second");
            collision_.insert(pair<string, const int*>("second", collision2_passed));
        }
        window.draw(background2_1);
//        window.draw(background2_2);
    }
    
    else if (map_name== "third"){
        if (foot_players == true){
            collision_.erase("third");
            collision_.insert(pair<string, const int*>("third", collision3_passed));
        }
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
        if (water_catch == true){
            collision_.erase("fourth");
            collision_.insert(pair<string, const int*>("fourth", collision4_passed));
        }
        window.draw(background4_1);
        window.draw(background4_2);
    }
    
    else if(map_name== "home"){
        if (obtained_light == true){
            collision_.erase("home");
            collision_.insert(pair<string, const int*>("home", collision7_passed));
        }
        window.draw(background7_1);
        window.draw(background7_2);
    }
    
    else if (map_name== "maze"){
        window.draw(background8);
    }
    
    else if (map_name== "interior_80"){
        window.draw(background9);
    }
    
    else if (map_name== "room_clement"){
        window.draw(background10);
    }
    
    else if (map_name== "bossfinal"){
        window.draw(background11);
        window.draw(background11_2);
    }
    
    else if (map_name== "hall"){
        window.draw(background12);
    }
    
    openDoorS(window);
    closeDoorS(window);
    
    //Flowers
    flowerList(window);

    for (auto const& np : npcs[map_name]) {
        sf::Vector2f pos2 = (*np).getPos();
         if(pos.y >= pos2.y)
         {
              if (trainer.state == "Speaking"){
                if ((*np).name == "clement") obtained_light = true;
                if ((*np).name == "digger") mr_fountain = true;
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
                if ((*np).name!="passeur" && (*np).name!="passeur2" && (*np).name!="passeur3" && (*np).name!="passeur4" && (*np).name!="passeur5") (*np).draw(window);
                if ( ((*np).name=="passeur" && catched==false) || ((*np).name=="passeur2" && water_catch==false) || ((*np).name=="passeur3" && obtained_light==false) || ((*np).name=="passeur4" && mr_fountain==false) || ((*np).name=="passeur5" && foot_players==false) ) (*np).draw(window);
            }
         }
    }
    
    trainer.draw(window, event, view);
    
    
    for (auto const& np : npcs[map_name]) {
        sf::Vector2f pos2 = (*np).getPos();
         if(pos.y < pos2.y)
         {
              if (trainer.state == "Speaking"){
                if ((*np).name == "clement") obtained_light = true;
                if ((*np).name == "digger") mr_fountain = true;
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
                if ( (*np).name!="passeur" && (*np).name!="passeur2" && (*np).name!="passeur3" && (*np).name!="passeur4" && (*np).name!="passeur5") (*np).draw(window);
                if ( ((*np).name=="passeur" && catched==false) || ((*np).name=="passeur2" && water_catch==false) || ((*np).name=="passeur3" && obtained_light==false) || ((*np).name=="passeur4" && mr_fountain==false) || ((*np).name=="passeur5" && foot_players==false) ) (*np).draw(window);
            }
         }
    }
    
   //draw the walls above the door to create the illusion of "entering"
    illuCenter(window);
    illuShop(window);
    illuTunnelR(window);
    illuTunnelL(window);
    illuGrandhall(window);
    illuBat80(window);
    
    
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
    shop.draw(window, view, event, trainer, backpack);
    center.draw(window, view, event, trainer, backpack);
    light(window, view);
    backpack.draw(window, view, event, trainer);
    box.draw(window, view, event, trainer, backpack);
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

sf::FloatRect Map::getViewBounds(const sf::View &view)
{
        sf::FloatRect rt;
        rt.left = view.getCenter().x - view.getSize().x/2.f;
        rt.top  = view.getCenter().y - view.getSize().y/2.f;
        rt.width  = view.getSize().x;
        rt.height = view.getSize().y;
        return rt;
}

void Map::light(sf::RenderWindow &window, sf::View &view){
    if (map_name == "second"){
        sf::FloatRect viewBounds = getViewBounds(view);
        //for the underground map, a circle of light around player
        sf::CircleShape shape(30.f);
        shape.setFillColor(sf::Color(0,0,0,150));
        shape.setPosition(viewBounds.left+viewBounds.width/2-30, viewBounds.top +viewBounds.height/2-30);

        // définit un contour faded tres large
        shape.setOutlineThickness(500.f);
        shape.setOutlineColor(sf::Color(0,0,0,245));
        window.draw(shape);
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

void Map::flowerList(sf::RenderWindow &window){
    map<string,vector<int>> flower_list = {
        {"first",
            {144,160,144,144,144,128,144,112,224,160,224,144,224,128,224,112,144,94,160,94,176,94,192,94,208,94,224,94}
        },
        {"fourth",
            //flowers around the tree
            {464,0,480,0,496,0,512,0,528,0,
             464,16,480,16,496,16,512,16,528,16,
             464,32,528,32,
             464,48,528,48,
             464,64,528,64,
             464,80,528,80,
             464,96,480,96,496,96,512,96,528,96,
            //flowers in grass
             32,32,112,48,
            //flowers neer pokecenter
            288,336,288,400,448,336,448,400
            }
        }
    };
    
    
    
    if (map_name == "first" || map_name == "fourth" || map_name == "home"){
        for (vector<int>::iterator it = flower_list[map_name].begin(); it < flower_list[map_name].end(); it+=2){
            movingFlower(window, *it, *(it+1));
        }
    }
}

void Map::illuGrandhall(sf::RenderWindow &window){

    if (map_name == "first"){
        for(int i = 0; i < 8; i++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(579 + 17 * i, 545, 16, 16));
            sprite.setPosition(176 + i * 16, 368);
            window.draw(sprite);
        }

        for(int i = 0; i < 3; i++){
            sf::Sprite sprite2;
            (sprite2).setTexture(texture_2);
            (sprite2).setTextureRect(sf::IntRect(579 + 17 * (6+i), 545, 16, 16));
            sprite2.setPosition(176 + (8+i) * 16, 368);
            window.draw(sprite2);
               }
    }
}

void Map::illuBat80(sf::RenderWindow &window){
    if (map_name == "home"){
          for(int i = 0; i < 2; i++){
            sf::Sprite sprite;
            (sprite).setTexture(texture_2);
            (sprite).setTextureRect(sf::IntRect(18 + 21*17 - i*17, 1038, 16, 16));
            sprite.setPosition(224 - i*16, 160);
            window.draw(sprite);
          }
    }
}

