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
 #include "openbackpack.hpp"
 
 
 int main()
 {
     
     //the intro by Julien
     /* if (startgame()==1) return 0; */
     
     //Initializing the window
     sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().height), "PoXemon");
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
          
     while (window.isOpen())
     {
         
         sf::Event event;
         window.pollEvent(event);
         if ((event.type == sf::Event::KeyPressed)&&((event.key.code == sf::Keyboard::P))) if(openbackpck()==1) window.close();
         if (event.type == sf::Event::Closed) window.close();
         window.clear(); //sf::Color(112,200,160)
         map1.draw(window,view, Arthur, clock, event);
         window.setView(view);
         window.display();
     }
 
     return 0;
 }
 
