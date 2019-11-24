#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
/* #include "ResourcePath.hpp" */
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "tilemap.hpp"
#include "trainer.hpp"
#include "const.hpp"
#include "npc.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(544*2, 544*2), "Tilemap");
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
    view.zoom(0.7f);
    window.setPosition(sf::Vector2i(0, 0));
    TileMap map;
    if (!map.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 34)) return -1;

    TileMap bigmap;
    if (!bigmap.load("Sprites/herbe.png", sf::Vector2u(16, 16), level2, 34,34 )) return -1;
    /* sf::Music music;
    if (!music.openFromFile(resourcePath() + "town_1.ogg")) {
        return EXIT_FAILURE;
    }
    music.play(); */
    
    int deltaT = 0;
    sf::Sprite spritePlayer;
    //Variables for the character and declaration of him/ we need to put it in constructor
    float playerMovementSpeed = 16;
    int sheetRect = 64;
    int sizeAnim = 4;
    
    Trainer Arthur(playerMovementSpeed, sheetRect, sizeAnim);
    //Test of our first Npc

    Npc Vieux;

    sf::Clock clock;
    
    window.setFramerateLimit(30);
    
    while (window.isOpen())
    {
        deltaT += 30;
//        clock.getElapsedTime().asMilliseconds();
        
        sf::Event event;
        window.pollEvent(event);
        if(event.type == sf::Event::Closed) window.close();
        
        
        sf::Time elapsed1 = clock.getElapsedTime();
        
    
        Arthur.setSpeed(event);
        Arthur.displacement(event,view, deltaT);     
        window.clear(sf::Color(112,200,160));     
        window.draw(map);
        
        Arthur.draw(window);
        Vieux.draw(window);

        window.setView(view);
        
        window.display();
    }

    return 0;
}

