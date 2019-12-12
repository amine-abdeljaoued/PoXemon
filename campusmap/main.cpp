#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include "tilemap.hpp"
#include "trainer.hpp"
#include "const.hpp"
#include "npc.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "intro.hpp"
#include "test.h"
#include "Backpack_content.h"
#include "Button.h"


//Function to create strings from values
template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}


int main()
{
//    menu("main_menu.jpg");
//    intro("professor1.png",1,0);
//    intro("professor4.png",1,1);
//    intro("professor3.png",0,2);
//    intro("professor5.png",0,3);
//    intro("professor2.png",0,4);
//    intro("professor6.png",1,5);
//    intro("professor7.png",1,6);
//    intro("professor1.png",0,7);
//    intro("professor4.png",0,8);
//    intro("professor6.png",1,9);
//    intro("professor5.png",1,10);
//    intro("professor3.png",0,11);
//    intro("professor2.png",0,12);
//    choice("professor0.png",1,13);
//    if(choice("professor0.png",1,14)==1) intro("professor7.png",0,15);
//    else{
//    intro("professor4.png",0,16);
//    intro("professor1.png",1,17);
//        int a = choose("professor0.png",1);
//        if(a==1) intro("professor5.png",0,18);
//        else if(a==2) intro("professor5.png",0,19);
//        else if(a==3) intro("professor5.png",0,20);
//        }

    
    std::string map_name = "first";
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "PoXemon");
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
    view.zoom(0.5f);
    
    window.setPosition(sf::Vector2i(0, 0));

    //Variables for the character and declaration of him/ we need to put it in constructor
    float playerMovementSpeed = 2;
    int sheetRect = 64;
    int sizeAnim = 4;
    
    Trainer Arthur(playerMovementSpeed, sheetRect, sizeAnim);
    
    // const for the transition
    sf::Clock clock;
    window.setFramerateLimit(30);
    
    Map map1(window, map_name);
    
    while (window.isOpen())
    {
        sf::Event event;
        window.pollEvent(event);
        
        if(event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B){
            
        }
        
        window.clear(sf::Color(112,200,160));
        sf::Time elapsed1 = clock.getElapsedTime();
        map1.draw(window,view, Arthur, clock, event, map_name);
        Arthur.displacement(event,view, case_num);
        window.setView(view);
        window.display();
    }

    return 0;
}

