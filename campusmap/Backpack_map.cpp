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
    
    if (!texture_background.loadFromFile(resourcePath() + "screen_menu.jpg")) {
        std::cout<<"error"<<std::endl;
    }
    if (!texture_backpack.loadFromFile(resourcePath() + "Pt_bag.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
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
    
    std::string name1 = "jistolwer";
    std::string name2 = "auron";
    std::string name3 = "husabus";
    Backpack_Pokemon poke1(name1, 50, 0, 50, 20);//not the actual types though
    Backpack_Pokemon poke2(name2, 56, 1, 60, 20);
    Backpack_Pokemon poke3(name3, 1, 2, 70, 30);
    backpack_pokemons[0] = &poke1;
    backpack_pokemons[1] = &poke2;
    backpack_pokemons[2] = &poke3;
    
    for (unsigned int i = 0; i < 3; i++) {
        backpack_pokemons[i]->health = 10;
        cout << backpack_pokemons[i]->health << endl;
    }
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
        backpack_graph.setPosition(sf::Vector2f(viewBounds.left+viewBounds.width/3.5, viewBounds.top+viewBounds.height/2));
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
        n_item.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/4.5, viewBounds.top + viewBounds.height/1.8));
        
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
    
    sf::FloatRect viewBounds = getViewBounds(view);
    
    //Create the column menu of the backpack to select the items(Only names of items)
    for (int i=0; i < 7; i++){
        menu[i].setCharacterSize(10);
        menu[i].setFillColor(sf::Color::Black);
        menu[i].setFont(font);
        menu[i].setPosition(viewBounds.left + viewBounds.width/2, viewBounds.top + (viewBounds.height/8)*(i+1));
        menu[i].setString(toString(item_type[i]));
    }
    menu[Selecteditem].setFillColor(sf::Color::White);
    
    //Create the column menu of the backpack to select the items(Only quantity of items)
    for (int i=0; i < 7; i++){
        quantity[i].setCharacterSize(10);
        quantity[i].setFillColor(sf::Color::Black);
        quantity[i].setFont(font);
        quantity[i].setPosition(viewBounds.left + viewBounds.width/2 + 100, viewBounds.top + (viewBounds.height/8)*(i+1));
        quantity[i].setString("x" + toString(inventory[item_type[i]]));
    }
    quantity[Selecteditem].setFillColor(sf::Color::White);
    
    //Draw the two columns: items_type and quantity
    for (int i = 0; i<7 ; i++) {
        window.draw(menu[i]);
        window.draw(quantity[i]);
    }
}

//Final Draw function for background and menu conditionally to the state
void BackpackMap::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer) {
    if (trainer.state=="Backpack") {
        draw_background(window, view, event, trainer);
        draw_menu(window, view, event, trainer);
    }
}

//Delete Function
void BackpackMap::Delete(sf::Event &event) {
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

//Function for moving up in the menu with the keyboard
void BackpackMap::Moveup(sf::Event &event) {
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

//Function for moving down in the menu with keyboard
void BackpackMap::Movedown(sf::Event &event) {
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

//Function that gives the current selected item (to implement after the delete button for example
int BackpackMap::getPresseditem() {
    return Selecteditem;
}
