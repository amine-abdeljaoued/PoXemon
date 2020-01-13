 #include <SFML/Audio.hpp>
 #include <SFML/Graphics.hpp>
 #include <SFML/OpenGL.hpp>
/*  #include "ResourcePath.hpp" */
 #include <SFML/Window.hpp>
 #include <unistd.h>
 #include <stdio.h>
 #include <iostream>
 #include <sstream>
 #include <string>
 #include <fstream>
 #include "tilemap.hpp"
 #include "trainer.hpp"
 #include "npc.hpp"
 #include "map.hpp"
 #include "intro.hpp"
 #include "const.hpp"
 #include "shop.hpp"

 //Files for fights
#include "fights/Pokemon.h"
#include "fights/Backpack.h"
#include "fights/Backpack_Pokemon.cpp"
#include "fights/Player.h"
#include "fights/Opponent.h"
#include "fights/Fight.h"



using namespace std;

 int main()
 {
     //the intro by Julien
     int poke_name = startgame();
     if (poke_name==0) poke_name = -1;
     if (poke_name==1) return 0;

     //Initializing the window
     sf::RenderWindow window(sf::VideoMode(1400, 700), "My window", sf::Style::Titlebar | sf::Style::Close);

     /* sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().height), "PoXemon"); */
     sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 272));
     view.zoom(0.6f);
     window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));

     // const for the transition
     sf::Clock clock;
     window.setFramerateLimit(30);

     //Variables for the character and declaration of him/ we need to put it in constructor
     float playerMovementSpeed = 2;
     int sheetRect = 32;
     int sizeAnim = 4;

     Trainer Arthur(playerMovementSpeed, sheetRect, sizeAnim);
     Map map1(window, -1);

     // For the fights
 	   Fight fight(window);
     bool start_fight = false;

     //TO NOT GET ANNOYED WITH FIGHTS:
     //JUST COMMENT in map.cpp in Fighting the trainer.state = "Fighting" in line 437
  
     sf::Music music;
     if (!music.openFromFile("Sprites/town_1.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music2;
     if (!music2.openFromFile("Sprites/pokeshop.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music3;
     if (!music3.openFromFile("Sprites/pokecenter.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music4;
     if (!music4.openFromFile("Sprites/hall.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music5;
     if (!music5.openFromFile("Sprites/cave.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music6;
     if (!music6.openFromFile("Sprites/town_2.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music7;
     if (!music7.openFromFile("Sprites/sports.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music8;
     if (!music8.openFromFile("Sprites/interior_80.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music9;
     if (!music9.openFromFile("Sprites/maze.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music10;
     if (!music10.openFromFile("Sprites/room_clement.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music11;
     if (!music11.openFromFile("Sprites/route_2.ogg")) std::cout << "Error loading music" << std::endl;
     sf::Music music12;
     if (!music12.openFromFile("Sprites/bossfinal.ogg")) std::cout << "Error loading music" << std::endl;
        
     string current = map1.map_name;

     music.play();
     music.setLoop(true);
  
     while (window.isOpen())
     {
         

         sf::Event event;
         window.pollEvent(event);

         if (event.type == sf::Event::Closed) window.close();
         window.clear(); //CHANGE AND PUT IN map.draw

         if(Arthur.state=="Fighting"){
             if(start_fight==false){ // must initialise the fight
                 view.reset(sf::FloatRect(0.f, 0.f, 1400.f, 700.f));
                 if(Arthur.fight_mode=='t'){
                     fight.initialise_trainer(map1.backpack, *(Arthur.opponent_bag), window);} // trainer fight
                 else {
                     fight.initialise_wild(map1.backpack, window);} // wild pokemon fight
                 start_fight = true;
             }
             else{
                int i = fight.update(window, map1.backpack, &map1.box);
                if(i==55){ //Won against trainer
                    Arthur.state = "Stop";
                    map1.check_opponents(*(Arthur.opponent_bag));
                }
                if(i==0){ Arthur.state = "Stop";}
                if(i==50 || i==60){Arthur.state = "Dead";}
                }
         }
         else{ //Not fighting
             if(start_fight==true){

                 start_fight = false;
                 sf::Vector2f position = Arthur.spritePlayer.getPosition();
                 view.setSize(sf::Vector2f(544.f, 272.f));
                 view.setCenter(sf::Vector2f(position.x, position.y));
                 view.zoom(0.6f);
             }
             map1.draw(window,view, Arthur, clock, event);

         }
      
         if(map1.map_name != current){
                if (current == "first") music.stop();
                else if (current == "pokeShop") music2.stop();
                else if (current == "pokeCenter") music3.stop();
                else if (current == "hall") music4.stop();
                else if (current == "second") music5.stop();
                else if (current == "home") music6.stop();
                else if (current == "third") music7.stop();
                else if (current == "interior_80") music8.stop();
                else if (current == "maze") music9.stop();
                else if (current == "room_clement") music10.stop();
                else if (current == "fourth") music11.stop();
                else if (current == "bossfinal") music12.stop();
                else music.stop();
                if (map1.map_name == "pokeShop"){
                    music2.play();
                    music2.setLoop(true);
                }
                else if (map1.map_name == "pokeCenter"){
                    music3.play();
                    music3.setLoop(true);
                }
                else if (map1.map_name == "first"){
                    music.play();
                    music.setLoop(true);
                }
                else if (map1.map_name == "hall"){
                    music4.play();
                    music4.setLoop(true);
                }
                else if (map1.map_name == "second"){
                    music5.play();
                    music5.setLoop(true);
                } //underground
                else if (map1.map_name == "home"){
                    music6.play();
                    music6.setLoop(true);
                }
                else if (map1.map_name == "third"){
                    music7.play();
                    music7.setLoop(true);
                } //sports
                else if (map1.map_name == "interior_80"){
                    music8.play();
                    music8.setLoop(true);
                }
                else if (map1.map_name == "maze"){
                    music9.play();
                    music9.setLoop(true);
                }
                else if (map1.map_name == "room_clement"){
                    music10.play();
                    music10.setLoop(true);
                }
                else if (map1.map_name == "fourth"){
                    music11.play();
                    music11.setLoop(true);
                }
                else if (map1.map_name == "bossfinal"){
                    music11.play();
                    music11.setLoop(true);
                }
                else{
                    music.play();
                    music.setLoop(true);
                }
                current = map1.map_name;
         }
    
         window.setView(view);
         window.display();
     }
     // to fix...
     return 0;
 }
