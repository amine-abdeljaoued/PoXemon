#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "ResourcePath.hpp"
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
#include "test.h"
#include "Backpack_content.h"
#include "Button.h"
#include "intro.hpp"
#include "const.hpp"


int main()
{
    //Initializing the window
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "PoXemon");
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
    view.zoom(0.5f);
    window.setPosition(sf::Vector2i(0, 0));
    
    // const for the transition
    sf::Clock clock;
    window.setFramerateLimit(30);
    
    //Variables for the character and declaration of him/ we need to put it in constructor
    float playerMovementSpeed = 2;
    int sheetRect = 32;
    int sizeAnim = 4;
    std::string map_name = "first";
    
    Trainer Arthur(playerMovementSpeed, sheetRect, sizeAnim);
    Map map1(window, map_name);
    
    //the intro by Julien
    if (startgame()==1) window.close();
    
    while (window.isOpen())
    {
        sf::Event event;
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) window.close();
        window.clear(sf::Color(112,200,160));
        sf::Time elapsed1 = clock.getElapsedTime();
        map1.draw(window,view, Arthur, clock, event, map_name);
        Arthur.displacement(event,view, case_num);
        window.setView(view);
        window.display();
    }

    return 0;
}

