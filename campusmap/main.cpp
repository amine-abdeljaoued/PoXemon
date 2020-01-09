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
     /* if (startgame()==1) return 0; */
     
     //Initializing the window
     sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");
	 float groundY = 300.0f; //Cannot go below this height - NB INITIALISE WITH WINDOW??
     float groundX = 1000.f;
     /* sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().height), "PoXemon"); */
     sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
     view.zoom(0.5f);
     window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));
     
     // const for the transition
     sf::Clock clock;
     window.setFramerateLimit(30);
     
     //Variables for the character and declaration of him/ we need to put it in constructor
     float playerMovementSpeed = 2;
     int sheetRect = 32;
     int sizeAnim = 4;
     
     Trainer Arthur(playerMovementSpeed, sheetRect, sizeAnim);
     Map map1(window);

     //Linking with fights

     //intialise the backpack and players: NOT NEEDED IN ACTUAL MAIN, they will exist already

 	Backpack bag;
	std::string name1 = "jistolwer";
	std::string name2 = "auron";
	std::string name3 = "husabus";
	Backpack_Pokemon poke1(name1, 1, 0, 50, 20);//not the actual types though
	Backpack_Pokemon poke2(name2, 1, 1, 60, 20);
	Backpack_Pokemon poke3(name3, 1, 2, 70, 30);
	bag.backpack_pokemons[0] = &poke1;
	bag.backpack_pokemons[1] = &poke2;
	bag.backpack_pokemons[2] = &poke3;

	Backpack opponent_bag;
	name1 = "donryle";
	name2 = "fepeur";
	name3 = "geodos";
	Backpack_Pokemon opoke1(name1, 1, 0, 50, 10);
	Backpack_Pokemon opoke2(name2, 1, 1, 60, 20);
	Backpack_Pokemon opoke3(name3, 1, 2, 70, 30);
	opponent_bag.backpack_pokemons[0] = &opoke1;
	opponent_bag.backpack_pokemons[1] = &opoke2;
	opponent_bag.backpack_pokemons[2] = &opoke3;

	Player* player = new Player(window, 200.f, 500.f, poke1);//by default, we take the first pokemon of the backpack
																			//do we want to be able to choose our pokemon at the beginning of the fight?
	Opponent* opponent = new Opponent(window, 200.f, 800.f, opoke1); 

	//ACTUAL MAIN: now for the fights...

 	Fight fight(window);
	char mode = 't'; // this is decided before
	//fight.initialise(mode, bag, opponent_bag, player, opponent, window); 

    //END OF FIGHTS INITIALISATION


    bool start_fight = false;
    

    //TO NOT GET ANNOYED WITH FIGHTS: 
    //JUST COMMENT LINE 359 of map.cpp
     while (window.isOpen())
     {
         //For the fights team uncomment this line:
         Arthur.state="Fighting";
         
         sf::Event event;
         window.pollEvent(event);
        /*  if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::P))) if(openbackpck()==1) window.close(); */
         if (event.type == sf::Event::Closed) window.close();
         window.clear(); //CHANGE AND PUT IN map.draw
         
         if(Arthur.state=="Fighting"){
             if(start_fight==false){ //Which means we're not already fighting
                 view.reset(sf::FloatRect(0.f, 0.f, 1400.f, 700.f));
                 fight.initialise(mode, bag, opponent_bag, player, opponent, window);
                 //This will allow us to initialise the fight how we want
                 //We can add to the fighting mode other parameters (opponent_bag is what matters)
                 start_fight = true;
             }
             else{
                int i = fight.update(window);
                // window.draw(fight.popponent-> sprite);
                if(i==0){
                // return to other state
                /* cout << "Exiting fights" <<endl; */
                Arthur.state = "Stop";
                /* view.setCenter(sf::Vector2f(0.f, 0.f));
                view.setSize(sf::Vector2f(1400.f, 700.f));
                view.zoom(0.5f); */
                }
                }
         }
         else{ //Not fighting
             /* view.zoom(0.5f); */
             if(start_fight==true){
                 start_fight = false;
                 sf::Vector2f position = Arthur.spritePlayer.getPosition();
                 view.setSize(sf::Vector2f(544.f, 544.f));
                 view.setCenter(sf::Vector2f(position.x, position.y));
                 view.zoom(0.5f);

             }
             map1.draw(window,view, Arthur, clock, event);
             
         }
         window.setView(view);
         window.display();
     }
     // to fix...
     delete player;
     delete opponent;
     return 0;
 }
 
