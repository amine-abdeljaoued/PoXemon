//
//  intro.cpp
//  Pokemen
//
//  Created by Julien Luzzatto on 05/12/2019.
//  Copyright © 2019 Julien Luzzatto. All rights reserved.
//

#include "intro.hpp"
#include <iostream>
#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

int intro(std::string picture, bool side, int which) {
    
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
    
    // Create a second line of graphical text to display
    sf::Text subtitle;

    subtitle.setFont(font);
    subtitle.setCharacterSize(70);
    subtitle.setStyle(sf::Text::Bold);
    subtitle.setFillColor(sf::Color::Black);
    subtitle.setPosition(WindowSize.x*(y)+WindowSize.x*(0.02), WindowSize.y*(0.15)+WindowSize.y*(0.10));
    
    // Create an explanation
    sf::Text expl("Press enter to go forward", font, 40);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    if (side == 1){
        expl.setPosition(WindowSize.x*(0.15), WindowSize.y*(0.90));
    }
    if (side == 0){
        expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));
    }
    
    
    if (which == 0){
    std::string str = "Hi! Sorry to keep you waiting!";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 1){
    std::string str = "Welcome to the world of Pokemen!";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 2){
    std::string str = "My name is Didy.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 3){
    std::string str = "But everyone calls me Professor Pokemen.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 4){
    std::string str = "The campus is widely inhabited by creatures";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "called Pokemen.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 5){
    std::string str = "We humans live alongside Pokemen,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 6){
    std::string str = "at times as friendly playmates,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "and at times as cooperative workmates.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 7){
    std::string str = "And sometimes, we band together";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "and battle others like us.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 8){
    std::string str = "But despite our closeness,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "we don't know everything about Pokemen.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }

    if (which == 9){
    std::string str = "In fact, there are many,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 10){
    std::string str = "many secrets surrounding Pokemen.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 11){
    std::string str = "To unravel Pokemen mysteries,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "I've been undertaking research.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 12){
    std::string str = "That's what I do.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 15){
    std::string str = "This is a shame. Have a nice journey home.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 16){
    std::string str = "You have to accept your Pokemen";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "with love and respect.";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 17){
    std::string str = "For that, I'll have you choose";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "one of my three precious Pokemon.";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 18){
    std::string str = "Excellent! Raporoy won't let you down";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "You are now ready to start!";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 19){
    std::string str = "Excellent! Wapefet won't let you down";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "You are now ready to start!";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 20){
    std::string str = "Excellent! Gangstakabra won't let you down";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "You are now ready to start!";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
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
        intro.draw(subtitle);
            if (which < 2){
                intro.draw(expl);
            }
        intro.display();
}
}
    return 99;
}

bool choice(std::string prof, bool side, int which) {
    
    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow choice(desktop, "Pokemen");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    choice.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a background to display
    
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "menu_2.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = choice.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create an image to appear
       
    sf::Texture image;
    if (!image.loadFromFile(resourcePath() + prof)) {
        return EXIT_FAILURE;
    }
    sf::Sprite professor;
    sf::Vector2u ImageSize;
    professor.scale(sf::Vector2f(5.f, 5.f)); //Set scale
        
    float x = 0.02; //which side of the screen
    float y = 0.42;
    if (side == 1){
        x = 0.60;
        y = 0.10;
    }
    professor.setPosition(WindowSize.x*(0.45), -650);
    professor.setTexture(image);
    
    // Create a dialogue box
    sf::RectangleShape dialogue(sf::Vector2f(1500.f, 400.f));
    dialogue.setOutlineThickness(20.f);
    dialogue.setOutlineColor(sf::Color(1, 1, 1));
    dialogue.setPosition(WindowSize.x*(y), WindowSize.y*(0.15));
    
    // Create a choice 1
    sf::RectangleShape choice1(sf::Vector2f(700.f, 200.f));
    choice1.setOutlineThickness(10.f);
    choice1.setOutlineColor(sf::Color(1, 1, 1));
    choice1.setPosition(WindowSize.x*(y), WindowSize.y*(0.55));
    
    // Create a choice 2
    sf::RectangleShape choice2(sf::Vector2f(700.f, 200.f));
    choice2.setOutlineThickness(10.f);
    choice2.setOutlineColor(sf::Color(1, 1, 1));
    choice2.setPosition(WindowSize.x*(y+0.24), WindowSize.y*(0.55));
    
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
    
    // Create a second line of graphical text to display
    sf::Text subtitle;

    subtitle.setFont(font);
    subtitle.setCharacterSize(70);
    subtitle.setStyle(sf::Text::Bold);
    subtitle.setFillColor(sf::Color::Black);
    subtitle.setPosition(WindowSize.x*(y)+WindowSize.x*(0.02), WindowSize.y*(0.15)+WindowSize.y*(0.10));
    
    // Create a first option
    sf::Text option1;

    option1.setFont(font);
    option1.setCharacterSize(70);
    option1.setStyle(sf::Text::Bold);
    option1.setFillColor(sf::Color::Black);
    option1.setPosition(WindowSize.x*(y)-WindowSize.x*(0.11), WindowSize.y*(0.55)+WindowSize.y*(0.03));
    
    // Create a second option
    sf::Text option2;

    option2.setFont(font);
    option2.setCharacterSize(70);
    option2.setStyle(sf::Text::Bold);
    option2.setFillColor(sf::Color::Black);
    option2.setPosition(WindowSize.x*(y+0.24)-WindowSize.x*(0.11), WindowSize.y*(0.55)+WindowSize.y*(0.03));
    
    // Create an explanation
    sf::Text expl("Press the left arrow for left choice, right arrow for the right choice", font, 40);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    if (side == 1){
        expl.setPosition(WindowSize.x*(0.15), WindowSize.y*(0.90));
    }
    if (side == 0){
        expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));
    }
    
    if (which == 13){
    std::string str = "And you?";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "What is your name?";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    std::string str_3 = "Boy";
        while (str_3.length() < 40){
            str_3 = " " + str_3;
        }
    option1.setString(str_3);
    std::string str_4 = "Girl";
        while (str_4.length() < 40){
            str_4 = " " + str_4;
        }
    option2.setString(str_4);
    }
    
    if (which == 14){
    std::string str = "And tell me, my friend,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "do you like Pokemon?";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    std::string str_3 = "Yes";
        while (str_3.length() < 40){
            str_3 = " " + str_3;
        }
    option1.setString(str_3);
    std::string str_4 = "No";
        while (str_4.length() < 40){
            str_4 = " " + str_4;
        }
    option2.setString(str_4);
    }
    
    
    // Start the game loop
    while (choice.isOpen())
    {
        // Process events
        sf::Event event;
        while (choice.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                choice.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                choice.close();
            }
        
            // Click button 1:
            if (event.type == sf::Event::KeyPressed)
            {
                if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)){
                    choice.close();
                    return 0;
                    }
                }
                
            // Click button 2:
            if (event.type == sf::Event::KeyPressed)
            {
                if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)){
                    choice.close();
                    return 1;
                    }
                }
            
        choice.clear();
        choice.draw(background);
        choice.draw(professor);
        choice.draw(dialogue);
        choice.draw(choice1);
        choice.draw(choice2);
        choice.draw(title);
        choice.draw(subtitle);
        choice.draw(option1);
        choice.draw(option2);
        choice.draw(expl);
        choice.display();
}
}
    return 0;
}


int choose(std::string prof, bool side) {
    
    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow choose(desktop, "Pokemen");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    choose.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a background to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "menu_3.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = choose.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create an image to appear
    sf::Texture image;
    if (!image.loadFromFile(resourcePath() + prof)) {
        return EXIT_FAILURE;
    }
    sf::Sprite professor;
    sf::Vector2u ImageSize;
    professor.scale(sf::Vector2f(5.f, 5.f)); //Set scale
        
    float x = 0.02; //which side of the screen
    float y = 0.42;
    if (side == 1){
        x = 0.60;
        y = 0.10;
    }
    professor.setPosition(WindowSize.x*(0.45), -650);
    professor.setTexture(image);
    
    // Create a dialogue box
    sf::RectangleShape dialogue(sf::Vector2f(1500.f, 400.f));
    dialogue.setOutlineThickness(20.f);
    dialogue.setOutlineColor(sf::Color(1, 1, 1));
    dialogue.setPosition(WindowSize.x*(y), WindowSize.y*(0.15));
    
    // Create a choice 1
    sf::RectangleShape choice1(sf::Vector2f(400.f, 200.f));
    choice1.setOutlineThickness(10.f);
    choice1.setOutlineColor(sf::Color(1, 1, 1));
    choice1.setPosition(WindowSize.x*(y), WindowSize.y*(0.60));
    
    // Create a choice 2
    sf::RectangleShape choice2(sf::Vector2f(400.f, 200.f));
    choice2.setOutlineThickness(10.f);
    choice2.setOutlineColor(sf::Color(1, 1, 1));
    choice2.setPosition(WindowSize.x*(y+0.17), WindowSize.y*(0.60));
    
    // Create a choice 3
    sf::RectangleShape choice3(sf::Vector2f(400.f, 200.f));
    choice3.setOutlineThickness(10.f);
    choice3.setOutlineColor(sf::Color(1, 1, 1));
    choice3.setPosition(WindowSize.x*(y+0.34), WindowSize.y*(0.60));
    
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
    title.setPosition(WindowSize.x*(y), WindowSize.y*(0.15)+WindowSize.y*(0.05));
    
    // Create a second line of graphical text to display
    sf::Text subtitle;

    subtitle.setFont(font);
    subtitle.setCharacterSize(70);
    subtitle.setStyle(sf::Text::Bold);
    subtitle.setFillColor(sf::Color::Black);
    subtitle.setPosition(WindowSize.x*(y)+WindowSize.x*(0.03), WindowSize.y*(0.15)+WindowSize.y*(0.10));
    
    // Create a first option
    sf::Text option1;

    option1.setFont(font);
    option1.setCharacterSize(50);
    option1.setStyle(sf::Text::Bold);
    option1.setFillColor(sf::Color::Black);
    option1.setPosition(WindowSize.x*(y)-WindowSize.x*(0.06), WindowSize.y*(0.60)+WindowSize.y*(0.03));
    
    // Create a second option
    sf::Text option2;

    option2.setFont(font);
    option2.setCharacterSize(50);
    option2.setStyle(sf::Text::Bold);
    option2.setFillColor(sf::Color::Black);
    option2.setPosition(WindowSize.x*(y+0.18)-WindowSize.x*(0.07), WindowSize.y*(0.60)+WindowSize.y*(0.03));
    
    // Create a third option
    sf::Text option3;

    option3.setFont(font);
    option3.setCharacterSize(50);
    option3.setStyle(sf::Text::Bold);
    option3.setFillColor(sf::Color::Black);
    option3.setPosition(WindowSize.x*(y+0.35)-WindowSize.x*(0.07), WindowSize.y*(0.60)+WindowSize.y*(0.03));

    
    // Create an explanation
    sf::Text expl("Press the left arrow for left choice, down arrow for the middle choice, right arrow for the right choice", font, 30);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    if (side == 1){
        expl.setPosition(WindowSize.x*(0.15), WindowSize.y*(0.90));
    }
    if (side == 0){
        expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));
    }
    
    std::string str = "Which Pokemon";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "would you like to start with?";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    std::string str_3 = "Raporoy"; // rouge
        while (str_3.length() < 30){
            str_3 = " " + str_3;
        }
    option1.setString(str_3);
    std::string str_4 = "Wapefet"; // bleu
        while (str_4.length() < 30){
            str_4 = " " + str_4;
        }
    option2.setString(str_4);
    std::string str_5 = "Gangstakabra"; // brown
        while (str_5.length() < 30){
            str_5 = " " + str_5;
        }
    option3.setString(str_5);
    
    
    // Start the game loop
    while (choose.isOpen())
    {
        // Process events
        sf::Event event;
        while (choose.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                choose.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                choose.close();
            }
        
            // Click button 1:
            if (event.type == sf::Event::KeyPressed)
            {
                if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)){
                    choose.close();
                    return 1;
                    }
                }
            
            // Click button 2:
            if (event.type == sf::Event::KeyPressed)
            {
                if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)){
                    choose.close();
                    return 2;
                    }
                }
                
            // Click button 3:
            if (event.type == sf::Event::KeyPressed)
            {
                if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)){
                    choose.close();
                    return 3;
                    }
                }
            
        choose.clear();
        choose.draw(background);
        choose.draw(professor);
        choose.draw(dialogue);
        choose.draw(choice1);
        choose.draw(choice2);
        choose.draw(choice3);
        choose.draw(title);
        choose.draw(subtitle);
        choose.draw(option1);
        choose.draw(option2);
        choose.draw(option3);
        choose.draw(expl);
        choose.display();
}
}
    return 99;
}
