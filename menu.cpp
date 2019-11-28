//
//  menu.cpp
//  Pokemen
//
//  Created by Julien Luzzatto on 28/11/2019.
//  Copyright © 2019 Julien Luzzatto. All rights reserved.
//

#include "menu.hpp"
#include <iostream>
#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

void menu(std::string picture) {
    
    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow menu(desktop, "Pokemen");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    menu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + picture)) {
        return EXIT_FAILURE;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = menu.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create a graphical text to display
       sf::Font font;
       if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
           return EXIT_FAILURE;
       }
       sf::Text title("Start Game", font, 70);
       title.setStyle(sf::Text::Bold);
       title.setFillColor(sf::Color::Black);
       title.setPosition(WindowSize.x*(0.455), WindowSize.y*(0.65));

    // Start the game loop
    while (menu.isOpen())
    {
        // Process events
        sf::Event event;
        while (menu.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                menu.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                menu.close();
            }
            
            // Click start button:
            if (event.type == sf::Event::MouseButtonPressed)
            {
                float spot_x = title.getPosition().x;
                float spot_y = title.getPosition().y;
                float end_x = title.getPosition().x + WindowSize.x*(0.10);
                float end_y = title.getPosition().y + WindowSize.y*(0.05);
                
                if ( (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x > (spot_x-20)) && (event.mouseButton.x < (end_x+20)) && (event.mouseButton.y > (spot_y-20)) && (event.mouseButton.y < (end_y+20)) ){
                    menu.close();
                    }
                }
            }
            menu.clear();
            menu.draw(background);
            menu.draw(title);
            menu.display();
        }
}
