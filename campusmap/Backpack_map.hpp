#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>
#include "trainer.hpp"
#include "fights/Backpack_Pokemon.cpp"

using namespace std;

class BackpackMap {
public:
    BackpackMap();
    
    void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    
    void Delete(sf::Event &event);
    
    void Moveup(sf::Event &event);
    void Movedown(sf::Event &event);
    
    std::map<std::string, int> inventory;
    
    sf::Text text;
    sf::Text n_item;
    sf::Text money_account;
    sf::Sprite background_screen;
    sf::Sprite backpack_graph;
    sf::Sprite rectangle;
    sf::Sprite money;
    
    int num_item();
    int getPresseditem();
    int Selecteditem;
    int number; //contains the actual number of items
    int wallet;
    
    Backpack_Pokemon* backpack_pokemons[3];
    
private:
    void draw_background(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    void draw_menu(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    
    int capacity;
    
    
    sf::Texture texture_background;
    sf::Texture texture_backpack;
    sf::Texture rectangle_texture;
    sf::Texture money_texture;
    sf::Font font;
    sf::Font font_menu;
    sf::Text menu[7];
    sf::Text quantity[7];
    sf::Text instruction;
    
    float width_backpack;
    float width_title;
    float width_i;
    bool arrow;
    bool release;
    
    sf::FloatRect getViewBounds(const sf::View &view);
};

//dictionnary giving the different possible existing items in the game
const std::string item_type[] = {
    "Normalball","Superball", "Masterball", "Incubator", "Starpowder", "SmallHealthPotion", "BigHealthPotion"
};

//Function to create strings from values
template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}
