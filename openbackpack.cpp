//
//  openbackpack.cpp
//  menu_2
//
//  Created by Florence Disset on 16/12/2019.
//  Copyright © 2019 clementsterlin. All rights reserved.
//

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "test.h"
#include "Backpack_content.h"
#include "Button.h"
#include "toString.h"
#include "Background.h"
#include "openbackpack.hpp"

int openbackpck(){
    // Create the main window
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window(desktop, "PoXemon");

    //Create backpack
    Backpack backpack;

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

    //Create all elements of the Background
    Background background(window.getSize().x, window.getSize().y, backpack);


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
                    background.n_item.setString("Items: " + toString(backpack.num_item()) + "/100");
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
                    background.n_item.setString("Items: " + toString(backpack.num_item()) + "/100");
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
        window.draw(background.background);
        
        // Draw the backpack
        window.draw(background.backpack_graph);

        // Draw the strings
        window.draw(background.text);
        window.draw(background.n_item);
       
        
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
    }
