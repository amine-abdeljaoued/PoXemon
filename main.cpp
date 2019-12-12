
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "test.h"
#include "Backpack_content.h"
#include "Button.h"

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

//Function to create strings from values
template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

int main(int, char const**)
{

    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window(desktop, "X-mon");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load background
    sf::Texture texture_back;
    if (!texture_back.loadFromFile(resourcePath() + "screen_menu.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture_back);
    background.setScale(7, 7);

    // Load backpack sprite
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "Pt_bag.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    //Set Backpack position
    float width_backpack = sprite.getGlobalBounds().width;
    sprite.setOrigin(sf::Vector2f(width_backpack/2, width_backpack/2));
    sprite.setPosition(sf::Vector2f(window.getSize().x/3.2, window.getSize().y/1.6));
    sprite.setScale(3, 3);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Backpack", font, 50);
    text.setFillColor(sf::Color::Black);
    
    
    //Set title position
    float width = text.getLocalBounds().width;
    text.setOrigin(sf::Vector2f(width/2, 0));
    text.setPosition(window.getSize().x/2, 0);
    
    //Create backpack
    Backpack backpack;
    
    //Create and set item display number
    sf::Text n_item;
    n_item.setString("Items: " + toString(backpack.num_item()) + "/100");
    n_item.setFont(font);
    n_item.setStyle(50);
    n_item.setFillColor(sf::Color::Black);
    
    float width_i = n_item.getLocalBounds().width;
    n_item.setOrigin(sf::Vector2f(width_i/2, 0));
    n_item.setPosition(sf::Vector2f((window.getSize().x/3.2)-(width_i/2)-10, window.getSize().y/1.6));
    
    //Create Menu
    Test menu(window.getSize().x, window.getSize().y);
    
    //Create Delete button
    Button del_button;
    del_button.Deletebutton(window.getSize().x, window.getSize().y);
    
    //Create Buy button
    Button buy_button;
    buy_button.Buyingbutton(window.getSize().x, window.getSize().y, backpack, menu);
    
    //Create Total money appearence
    Button money_appear;
    money_appear.Money(backpack);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    menu.Movedown();
                    buy_button.Buyingbutton(window.getSize().x, window.getSize().y, backpack, menu);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    menu.Moveup();
                    buy_button.Buyingbutton(window.getSize().x, window.getSize().y, backpack, menu);
                }
            }
            
            //If left click with mousse on delete button, and number of element of selected item is greater than 0, then delete one element and update the item number of element.
            if (del_button.isSpriteHover(del_button.button.getGlobalBounds(), sf::Vector2f(event.mouseButton.x,event.mouseButton.y)) == true) {
                 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (backpack.inventory[item_type[menu.Selecteditem]]>0) {
                        backpack.inventory[item_type[menu.Selecteditem]]--;
                    }
                    n_item.setString("Items: " + toString(backpack.num_item()) + "/100");
                }
            }
            
            //If left click with mousse on buy button, and number of elements smaller than maximal capacity, then buy one element and update the item number of element.
            if (buy_button.isSpriteHover(buy_button.button.getGlobalBounds(), sf::Vector2f(event.mouseButton.x,event.mouseButton.y)) == true) {
                 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (backpack.num_item() < backpack.capacity && backpack.wallet >= backpack.cost[item_type[menu.Selecteditem]]) {
                        backpack.inventory[item_type[menu.Selecteditem]]++;
                        backpack.wallet = backpack.wallet - backpack.cost[item_type[menu.Selecteditem]];
                        money_appear.money_account.setString(toString(backpack.wallet));
                    }
                    n_item.setString("Items: " + toString(backpack.num_item()) + "/100");
                }
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
                
            }
        }
        
        // Clear screen
        window.clear();

        //Draw the background
        window.draw(background);
        
        // Draw the backpack
        window.draw(sprite);

        // Draw the strings
        window.draw(text);
        window.draw(n_item);
       
        
        //Draw Menu;
        menu.drawing(window, backpack);
        
        //Draw Delete button
        window.draw(del_button.button);
        window.draw(del_button.title);
        
        //Draw Buy button
        window.draw(buy_button.button);
        window.draw(buy_button.title);
        window.draw(buy_button.money);
        
        //Draw Total amount of money
        window.draw(money_appear.button);
        window.draw(money_appear.money);
        window.draw(money_appear.money_account);

        // Update the window
        window.display();
        
    }

    return EXIT_SUCCESS;
}
