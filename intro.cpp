//
//  intro.cpp
//  Pokemen
//
//  Created by Julien Luzzatto on 05/12/2019.
//  Copyright © 2019 Julien Luzzatto. All rights reserved.
//

#include "intro.hpp"
#include <iostream>
#include <algorithm>
#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

void intro(std::string picture, bool side, int which) {
    
    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow intro(desktop, "Pokemen");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    intro.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a background to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "menu_2.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = intro.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create an image to appear
       
    sf::Texture image;
    if (!image.loadFromFile(resourcePath() + picture)) {
        return EXIT_FAILURE;
    }
    sf::Sprite professor;
    sf::Vector2u ImageSize;
    professor.scale(sf::Vector2f(3.f, 3.f)); //Set scale
        
    float x = 0.02; //which side of the screen
    float y = 0.42;
    if (side == 1){
        x = 0.60;
        y = 0.10;
    }
    professor.setPosition(WindowSize.x*(x), WindowSize.y*(0.25));
    professor.setTexture(image);
    
    // Create a dialogue box
    sf::RectangleShape dialogue(sf::Vector2f(1500.f, 400.f));
    dialogue.setOutlineThickness(20.f);
    dialogue.setOutlineColor(sf::Color(1, 1, 1));
    dialogue.setPosition(WindowSize.x*(y), WindowSize.y*(0.15));
    
    // Create a graphical text to display
    sf::Text title;
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    title.setFont(font);
    title.setCharacterSize(70);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    title.setPosition(WindowSize.x*(y)+WindowSize.x*(0.02), WindowSize.y*(0.15)+WindowSize.y*(0.05));
    
    if (which == 0){
    std::string str = "Hi! Sorry to keep you waiting!";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 1){
    std::string str = "Welcome to the world of Pokemen!";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 2){
    std::string str = "My name is Didy.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 3){
    std::string str = "But everyone calls me Professor Pokemen.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 4){
    std::string str = "The campus is widely inhabited by creatures";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 5){
    std::string str = "called Pokemen.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 6){
    std::string str = "We humans live alongside Pokemon,";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 7){
    std::string str = "at times as friendly playmates, and";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 8){
    std::string str = "at times as cooperative workmates.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 9){
    std::string str = "And sometimes, we band together";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 10){
    std::string str = "and battle others like us.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 11){
    std::string str = "But despite our closeness,";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 12){
    std::string str = "we don't know everything about Pokemen.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }

    if (which == 13){
    std::string str = "In fact, there are many,";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 14){
    std::string str = "many secrets surrounding Pokemen.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 15){
    std::string str = "To unravel Pokemen mysteries,";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 16){
    std::string str = "I've been undertaking research.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 17){
    std::string str = "That's what I do.";
    size_t n = std::count(str.begin(), str.end(), '_');
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    // Start the game loop
    while (intro.isOpen())
    {
        // Process events
        sf::Event event;
        while (intro.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                intro.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                intro.close();
            }
            
            // Advance button:
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
                    intro.close();
                }
            }
        intro.clear();
        intro.draw(background);
        intro.draw(professor);
        intro.draw(dialogue);
        intro.draw(title);
        intro.display();
        }
}
}
