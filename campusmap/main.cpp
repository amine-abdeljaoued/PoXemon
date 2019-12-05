#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
 #include "ResourcePath.hpp"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "tilemap.hpp"
#include "trainer.hpp"
#include "const.hpp"
#include "npc.hpp"
#include "map.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(544, 544), "Tilemap");
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
//    view.zoom(0.5f);
    window.setPosition(sf::Vector2i(0, 0));

    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Bonjour, je suis\nvotre premier PNJ", font, 24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(100, 100);
    text.setStyle(sf::Text::Bold);
    sf::RectangleShape rectangle(sf::Vector2f(230, 60));
    rectangle.setPosition(90, 100);

    /* sf::Music music;
    if (!music.openFromFile(resourcePath() + "town_1.ogg")) {
        return EXIT_FAILURE;
    }
    music.play(); */


    //Variables for the character and declaration of him/ we need to put it in constructor
    float playerMovementSpeed = 4;
    int sheetRect = 64;
    int sizeAnim = 4;
    int map_num = 0;
    int coll_num = 0;
    
    Trainer Arthur(playerMovementSpeed, sheetRect, sizeAnim, map_num, coll_num);
    
    // const for the transition
    int alpha = 250;
    sf::Clock clock;
    
    window.setFramerateLimit(30);
    
    while (window.isOpen())
    {
        
        sf::Event event;
        window.pollEvent(event);
        if(event.type == sf::Event::Closed) window.close();
        
        window.clear(sf::Color(112,200,160));
        
        Arthur.displacement(event,view, collision, clock, alpha, case_num);

        sf::Time elapsed1 = clock.getElapsedTime();
        
        Map map1(Arthur.map_num, window);
        map1.draw(window, Arthur, clock, alpha);
//        sf::RectangleShape rectangle(sf::Vector2f(524, 50));
//        rectangle.setPosition(10, 480);
//        rectangle.setOutlineColor(sf::Color::Red);
//        rectangle.setOutlineThickness(2);
//        if (Arthur.coll_num == 8) window.draw(rectangle);
        if (Arthur.coll_num == 8){
            window.draw(rectangle);
            window.draw(text);
        }
        window.setView(view);
     

        window.display();
    }

    return 0;
}

