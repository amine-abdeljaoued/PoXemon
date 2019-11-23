#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "tilemap.hpp"
#include "trainer.hpp"
#include "const.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(544*2, 544*2), "Tilemap");
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
    view.zoom(0.5f);
    window.setPosition(sf::Vector2i(0, 0));
    TileMap map;
    
    int deltaT = 0;
    
    sf::Texture texturePlayer;
    if (!texturePlayer.loadFromFile(/* resourcePath() + */ "Sprites/fullch.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite spritePlayer(texturePlayer);

    spritePlayer.setTextureRect(sf::IntRect(0,0,64,64));
    spritePlayer.setScale(sf::Vector2f(0.5f, 0.5f));
    spritePlayer.setPosition(262, 272);
    //Variables for the character
    float playerMovementSpeed = 16;
    int sheetRect = 64;
    int sizeAnim = 4;
    
    Trainer Arthur( &spritePlayer , playerMovementSpeed, sheetRect, sizeAnim);




    
    if (!map.load("Sprites/tileset1.png", sf::Vector2u(16, 16), level, 34, 34)) return -1;

    

    TileMap bigmap;
    
    if (!bigmap.load("Sprites/herbe.png", sf::Vector2u(16, 16), level2, 34,34 )) return -1;
    
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
        
        window.draw(spritePlayer);

        window.setView(view);
        
        window.display();
    }

    return 0;
}

