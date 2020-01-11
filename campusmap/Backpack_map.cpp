#include "Backpack_map.hpp"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "ResourcePath.hpp"

BackpackMap::BackpackMap() {
    
    //Load textures for backpack
    if (!rectangle_texture.loadFromFile(resourcePath() + "button.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!money_texture.loadFromFile(resourcePath() + "money.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!texture_background.loadFromFile(resourcePath() + "screen_menu.jpg")){
        std::cout<<"error"<<std::endl;
    }
    if (!texture_backpack.loadFromFile(resourcePath() + "Pt_bag.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        std::cout<<"error"<<std::endl;
    }
    if (!slots.loadFromFile(resourcePath() + "poke_slot.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!types.loadFromFile(resourcePath() + "poke_type.png")) {
        std::cout<<"error"<<std::endl;
    }
    
    //Set number of element of each item at beginning of game
    inventory["Normalball"] = 3;
    inventory["Superball"] = 2;
    inventory["Masterball"] = 1;
    inventory["Incubator"] = 0;
    inventory["Starpowder"] = 0;
    inventory["SmallHealthPotion"] = 2;
    inventory["BigHealthPotion"] = 1;
    
    //Set maximal capacity of backpack
    capacity = 30;
    
    //Set money available at begin of game
    wallet = 300;
    
    //Initialize the value Selecteditem to 0
    Selecteditem = 0;
    
    //Set the right column by default when open Backpack
    actual_column = 1;
    
    release = true;
    arrow = true;
    release_left = true;
    release_right = true;
    
    //Set Background texture
        background_screen.setTexture(texture_background);
        
        //Set backpack texture
        backpack_graph.setTexture(texture_backpack);
        
        //Set title Color, Position and Font
        text.setString("Backpack");
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        
        //implement the 3 objects for the money counter in the top left of the backpack window
        rectangle.setTexture(rectangle_texture);
        
        money_account.setFont(font);
        money_account.setFillColor(sf::Color::Black);
        
        money.setTexture(money_texture);
        
        //Implementing text for instruction
        instruction.setFont(font);
        instruction.setFillColor(sf::Color::Black);
        instruction.setString("Press [D] to Delete element");
        
        //Set pokemon
        std::string name1 = "jistolwer";
        std::string name2 = "auron";
        std::string name3 = "husabus";
        Backpack_Pokemon *poke1 = new Backpack_Pokemon(name1, 1, 0, 50, 10);
        Backpack_Pokemon *poke2 = new Backpack_Pokemon(name2, 1, 1, 60, 20);
        Backpack_Pokemon *poke3 = new Backpack_Pokemon(name3, 1, 2, 70, 30);
        backpack_pokemons[0] = poke1;
        backpack_pokemons[1] = poke2;
        backpack_pokemons[2] = poke3;
        
        
        //For Display of Pokemon in bag
        
        //Set textures for each sprite for pokemon
        empty_slot.setTexture(slots);
        empty_slot.setTextureRect(sf::IntRect(256,274,142,22));
        
        not_selected_slot.setTexture(slots);
        not_selected_slot.setTextureRect(sf::IntRect(256,178,142,22));
        
        selected_slot.setTexture(slots);
        selected_slot.setTextureRect(sf::IntRect(256,202,142,22));
        
        poke_close.setTexture(slots);
        poke_close.setTextureRect(sf::IntRect(18,194,20,20));
        
        poke_open.setTexture(slots);
        poke_open.setTextureRect(sf::IntRect(42,192,20,24));
        
        //Set types textures
        earth.setTexture(types);
        earth.setTextureRect(sf::IntRect(0,17,32,14));
        
        water.setTexture(types);
        water.setTextureRect(sf::IntRect(96,33,32,14));
        
        air.setTexture(types);
        air.setTextureRect(sf::IntRect(64,1,32,14));
        
        fire.setTexture(types);
        fire.setTextureRect(sf::IntRect(64,33,32,14));
        
        Selecteditem_pokemon = 0;
    }

    //Function to get the bounds of the window in order to draw at the middle of the window
    sf::FloatRect BackpackMap::getViewBounds(const sf::View &view)
    {
            sf::FloatRect rt;
            rt.left = view.getCenter().x - view.getSize().x/2.f;
            rt.top  = view.getCenter().y - view.getSize().y/2.f;
            rt.width  = view.getSize().x;
            rt.height = view.getSize().y;
            return rt;
    }

    //Method that returns total number of items in your backpack
    int BackpackMap::num_item() {
        
        //reset to 0
        number = 0;
     
        // Create a map iterator and point to beginning of map
        std::map<std::string, int>::iterator it = inventory.begin();
     
        // Iterate over the map using Iterator till end.
        while (it != inventory.end())
        {
            // Accessing number from the item pointed by it.
            int count = it->second;
     
            number += count;
     
            // Increment the Iterator to point to the next item
            it++;
        }
        return number;
    }

    //Function to draw all the simple graphics elements, such as sprites, background, titles
    void BackpackMap::draw_background(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer) {
        
            Delete(event);
        
            sf::FloatRect viewBounds = getViewBounds(view);
            
            //Position backpack on window
            width_backpack = backpack_graph.getGlobalBounds().width;
            backpack_graph.setOrigin(sf::Vector2f(width_backpack/2, width_backpack/2));
            backpack_graph.setPosition(sf::Vector2f(viewBounds.left+viewBounds.width/3.5, viewBounds.top+viewBounds.height/1.3));
            backpack_graph.setScale(0.8, 0.8);

            //Title
            text.setCharacterSize(15);
            width_title = text.getLocalBounds().width;
            text.setOrigin(sf::Vector2f(width_title/2, 0));
            text.setPosition(viewBounds.left+viewBounds.width/2, viewBounds.top);
            
            //Background
            background_screen.setPosition(viewBounds.left, viewBounds.top);
            background_screen.setScale(4, 4);
            
            //Set Display of total number of items
            n_item.setString("Items: " + toString(num_item()) + "/" + toString(capacity));
            n_item.setFont(font);
            n_item.setCharacterSize(10);
            n_item.setFillColor(sf::Color::Black);
            
            width_i = n_item.getLocalBounds().width;
            n_item.setOrigin(sf::Vector2f(width_i/2, 0));
            n_item.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/4.5, viewBounds.top + viewBounds.height/1.23));
            
            //Money Counter
            money.setScale(0.1, 0.1);
            money.setPosition(viewBounds.left + 30, viewBounds.top + 3);
        
            rectangle.setScale(0.16, 0.16);
            rectangle.setPosition(viewBounds.left + 2, viewBounds.top + 2);
        
            money_account.setString(toString(wallet));
            money_account.setCharacterSize(8);
            money_account.setPosition(viewBounds.left + 10, viewBounds.top + 5);
        
            //Instruction
            instruction.setCharacterSize(8);
            instruction.setPosition(viewBounds.left + 5 , viewBounds.top + viewBounds.height - 20);
        
            
            window.draw(background_screen);
            window.draw(backpack_graph);
            window.draw(text);
            window.draw(n_item);
            window.draw(rectangle);
            window.draw(money_account);
            window.draw(money);
            window.draw(instruction);
    }

    //Implement the draw function for the menu, the more complex element
    void BackpackMap::draw_menu(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer) {
        
        Delete(event);
        Moveup(event);
        Movedown(event);
        Moveleft(event);
        
        sf::FloatRect viewBounds = getViewBounds(view);
        
        //Create the column menu of the backpack to select the items(Only names of items)
        for (int i=0; i < 7; i++){
            menu[i].setCharacterSize(10);
            menu[i].setFillColor(sf::Color::Black);
            menu[i].setFont(font);
            menu[i].setPosition(viewBounds.left + viewBounds.width/2, viewBounds.top + (viewBounds.height/8)*(i+1));
            menu[i].setString(toString(item_type[i]));
        }
        
        if (actual_column == 1) {
            menu[Selecteditem].setFillColor(sf::Color::White);
        }

        //Create the column menu of the backpack to select the items(Only quantity of items)
        for (int i=0; i < 7; i++){
            quantity[i].setCharacterSize(10);
            quantity[i].setFillColor(sf::Color::Black);
            quantity[i].setFont(font);
            quantity[i].setPosition(viewBounds.left + viewBounds.width/2 + 100, viewBounds.top + (viewBounds.height/8)*(i+1));
            quantity[i].setString("x" + toString(inventory[item_type[i]]));
        }
        
        if (actual_column == 1) {
            quantity[Selecteditem].setFillColor(sf::Color::White);
        }
        
        //Draw the two columns: items_type and quantity
        for (int i = 0; i<7 ; i++) {
            window.draw(menu[i]);
            window.draw(quantity[i]);
        }
    }

    void BackpackMap::draw_pokemon(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer) {
        
        Moveright(event);
        Moveup_Pokemon(event);
        Movedown_Pokemon(event);
        
        sf::FloatRect viewBounds = getViewBounds(view);
        
        for (int i=0; i<3; i++) {
            empty_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
            empty_slot.setScale(0.8, 1);
            
            window.draw(empty_slot);
        }
        
        if (actual_column == 0) {
            for (int i=0; i<3; i++) {
                if (backpack_pokemons[i]->name != "Empty") {
                    if (i != Selecteditem_pokemon) {
                        not_selected_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
                        not_selected_slot.setScale(0.8, 1);
                        
                        window.draw(not_selected_slot);
                    }
                    else {
                        selected_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
                        selected_slot.setScale(0.8, 1);
                        
                        window.draw(selected_slot);
                    }
                }
            }
        }
        else {
            for (int i=0; i<3; i++) {
                if (backpack_pokemons[i]->name != "Empty") {
                    not_selected_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
                    not_selected_slot.setScale(0.8, 1);
                    
                    window.draw(not_selected_slot);
                }
            }
        }
        
        if (actual_column == 0) {
            for (int i=0; i<3; i++) {
                if (backpack_pokemons[i]->name != "Empty") {
                    if (i == Selecteditem_pokemon) {
                        poke_open.setOrigin(10, 12);
                        poke_open.setPosition(viewBounds.left+15, viewBounds.top + viewBounds.height/3.8 +(i*24) + 11);
                        
                        window.draw(poke_open);
                    }
                    else {
                        poke_close.setOrigin(10, 10);
                        poke_close.setPosition(viewBounds.left+15, viewBounds.top + viewBounds.height/3.8 +(i*24) +11);
                    
                        
                        window.draw(poke_close);
                    }
                }
            }
        }
        else {
            for (int i=0; i<3; i++) {
                if (backpack_pokemons[i]->name != "Empty") {
                    poke_close.setOrigin(10, 10);
                    poke_close.setPosition(viewBounds.left+15, viewBounds.top + viewBounds.height/3.8 +(i*24) +11);
                    
                    window.draw(poke_close);
                }
            }
        }
        
        //Draw health bar
        for (int i=0; i<3; i++) {
            if (backpack_pokemons[i]->name != "Empty") {
                sf::RectangleShape health_bar;
                health_poke = (float) (backpack_pokemons[i]->health)/100;
                health_bar.setSize(sf::Vector2f(38.5*health_poke,3));
                health_bar.setPosition(viewBounds.left+85.5, viewBounds.top + viewBounds.height/3.8 + (i*24) + 8);
                if (health_poke >= 0.5) {
                    health_bar.setFillColor(sf::Color::Green);
                }
                else if (0.2 <= health_poke && health_poke< 0.5){
                    health_bar.setFillColor(sf::Color(255,140,0));
                }
                else if (health_poke < 0.2){
                    health_bar.setFillColor(sf::Color::Red);
                }
                window.draw(health_bar);
            }
        }
        
        //Draw Names and level of pokemon in backpack
        for (int i=0; i<3; i++) {
            if (backpack_pokemons[i]->name != "Empty") {
                poke_name.setString(backpack_pokemons[i]->name);
                level.setString("lvl " + toString(backpack_pokemons[i]->level));
                poke_name.setCharacterSize(10);
                level.setCharacterSize(10);
                poke_name.setFillColor(sf::Color::White);
                level.setFillColor(sf::Color::White);
                poke_name.setFont(font);
                level.setFont(font);
                poke_name.setPosition(viewBounds.left+30, viewBounds.top + viewBounds.height/3.8 +(i*24));
                level.setPosition(viewBounds.left+40, viewBounds.top + viewBounds.height/3.8 +(i*24)+10);
                
                window.draw(poke_name);
                window.draw(level);
            }
        }
        
        //Draw Pokemon Type
        for (int i=0; i<3; i++) {
            if (backpack_pokemons[i]->name != "Empty"){
                if (backpack_pokemons[i]->type == 10) {
                    earth.setScale(0.6, 0.4);
                    earth.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                    window.draw(earth);
                }
                if (backpack_pokemons[i]->type== 20) {
                    water.setScale(0.6, 0.4);
                    water.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                    window.draw(water);
                }
                if (backpack_pokemons[i]->type == 30) {
                    air.setScale(0.6, 0.4);
                    air.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                    window.draw(air);
                }
                if (backpack_pokemons[i]->type == 40) {
                    fire.setScale(0.6, 0.4);
                    fire.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                    window.draw(fire);
                }
            }
        }
    }

    //Final Draw function for background and menu conditionally to the state
    void BackpackMap::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer) {
        if (trainer.state=="Backpack") {
            draw_background(window, view, event, trainer);
            draw_menu(window, view, event, trainer);
            draw_pokemon(window, view, event, trainer);
        }
    }

    //Delete Function
    void BackpackMap::Delete(sf::Event &event) {
        if (actual_column == 1) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::D&&release == true){
                if (inventory[item_type[Selecteditem]]>0) {
                    inventory[item_type[Selecteditem]]--;
                }
                release = false;
            }
            
            //bool release to check if key D is release or not
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::D){
                release = true;
            }
        }
    }

    //Function for moving up in the menu with the keyboard
    void BackpackMap::Moveup(sf::Event &event) {
        if (actual_column == 1) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up&&arrow == true){
                if (Selecteditem - 1 >= 0) {
                    menu[Selecteditem].setFillColor(sf::Color::Black);
                    Selecteditem--;
                    menu[Selecteditem].setFillColor(sf::Color::White);
                }
                arrow = false;
            }
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Up){
                arrow = true;
            }
        }
    }

    //Function for moving down in the menu with keyboard
    void BackpackMap::Movedown(sf::Event &event) {
        if (actual_column==1) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Down&&arrow == true){
                if (Selecteditem + 1 <= 6) {
                    menu[Selecteditem].setFillColor(sf::Color::Black);
                    Selecteditem++;
                    menu[Selecteditem].setFillColor(sf::Color::White);
                }
                arrow = false;
            }
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
                arrow = true;
            }
        }
    }

    void BackpackMap::Moveup_Pokemon(sf::Event &event) {
        if (actual_column==0) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up&&arrow == true){
                if (Selecteditem_pokemon > 0) {
                    Selecteditem_pokemon--;
                }
                arrow = false;
            }
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Up){
                arrow = true;
            }
        }
    }

    void BackpackMap::Movedown_Pokemon(sf::Event &event) {
        if (actual_column==0) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Down&&arrow == true){
                if (Selecteditem_pokemon < 2 && backpack_pokemons[Selecteditem_pokemon+1]->name != "Empty") {
                    Selecteditem_pokemon++;
                }
                arrow = false;
            }
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
                arrow = true;
            }
        }
    }

    void BackpackMap::Moveleft(sf::Event &event) {
        if (actual_column==1) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Left&&release == true){
                actual_column = 0;
                release_left = false;
            }
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Left){
                release_left = true;
            }
        }
    }

    void BackpackMap::Moveright(sf::Event &event) {
        if (actual_column==0) {
            if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Right&&release == true){
                actual_column = 1;
                release_right = false;
            }
            else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Right){
                release_right = true;
            }
        }
    }

    //Function that gives the current selected item (to implement after the delete button for example
    int BackpackMap::getPresseditem() {
        return Selecteditem;
    }
