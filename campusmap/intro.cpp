#include "intro.hpp"
#include <iostream>
/* #include "ResourcePath.hpp" */
#include <SFML/Audio.hpp>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

//This is the menu that appears at the beggining of the game

int menu(std::string picture) {
    
    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow menu(desktop, "PoXemon");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("Sprites/icon.png")) {
        std::cout << "Error" << std::endl;
    }
    menu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(/* resourcePath() + */ picture)) {
        std::cout << "Error" << std::endl;
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
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout << "Error" << std::endl;
    }
    sf::Text title("Start Game", font, 70);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    title.setPosition(WindowSize.x*(0.455), WindowSize.y*(0.65));
    
    // Create an explanation
    sf::Text expl("Click start game or press x to go forward", font, 40);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));

    // Start the game loop
    while (menu.isOpen())
    {
        // Process events
        sf::Event event;
        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) return 10;
            // Advance button:
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::X)) menu.close();
            
            // Click start button:
            if (event.type == sf::Event::MouseButtonPressed)
            {
                float spot_x = title.getPosition().x;
                float spot_y = title.getPosition().y;
                float end_x = title.getPosition().x + WindowSize.x*(0.10);
                float end_y = title.getPosition().y + WindowSize.y*(0.05);
                
                if ( (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x > (spot_x-20)) && (event.mouseButton.x < (end_x+20)) && (event.mouseButton.y > (spot_y-20)) && (event.mouseButton.y < (end_y+20)) ) menu.close();
                }
            }
            menu.clear();
            menu.draw(background);
            menu.draw(title);
            menu.draw(expl);
            menu.display();
        }
    return 0;
}

int startgame(){
    sf::Event event;
    int closed=0;
    closed = menu("Sprites/main_menu.jpg");
    if (closed<10) closed = loadgame("Sprites/main_menu.jpg");
    if (closed==9) return 0;
    if (closed<10)closed = intro("Sprites/professor1.png",1,0);
    if (closed<10)closed = intro("Sprites/professor4.png",1,1);
    if (closed<10)closed = intro("Sprites/professor3.png",0,2);
    if (closed<10)closed = intro("Sprites/professor5.png",0,3);
    if (closed<10)closed = intro("Sprites/professor2.png",0,4);
    if (closed<10)closed = intro("Sprites/professor6.png",1,5);
    if (closed<10)closed = intro("Sprites/professor7.png",1,6);
    if (closed<10)closed = intro("Sprites/professor1.png",0,7);
    if (closed<10)closed = intro("Sprites/professor4.png",0,8);
    if (closed<10)closed = intro("Sprites/professor6.png",1,9);
    if (closed<10)closed = intro("Sprites/professor5.png",1,10);
    if (closed<10)closed = intro("Sprites/professor3.png",0,11);
    if (closed<10)closed = intro("Sprites/professor2.png",0,12);
    if (closed<10)closed = choice("Sprites/professor0.png",1,13);
    if (closed<10){
        if(choice("Sprites/professor0.png",1,14)==1) {
            if(closed<10)closed=intro("Sprites/professor7.png",0,15);
            return 1;
        }
        else{
          if (closed<10)closed = intro("Sprites/professor4.png",0,16);
          if (closed<10)closed = intro("Sprites/professor1.png",1,17);
          if (closed<10) closed= choose("Sprites/professor0.png",1);
          if(closed==1) closed = intro("Sprites/professor5.png",0,18);
          else if(closed==2) closed = intro("Sprites/professor5.png",0,19);
          else if(closed==3) closed = intro("Sprites/professor5.png",0,20);
        }
    }
    if (closed<10) return 0;
    else return 1;
}
