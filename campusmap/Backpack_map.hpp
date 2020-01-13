#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>
#include "trainer.hpp"
#include "fights/Pokemon_Button.h"

using namespace std;

class BackpackMap {
public:
    BackpackMap();
    
    void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    
    void Delete(sf::Event &event);
    
    void Moveup(sf::Event &event);
    void Movedown(sf::Event &event);
    
    void Moveup_Pokemon(sf::Event &event);
    void Movedown_Pokemon(sf::Event &event);
    
    void Moveleft(sf::Event &event);
    void Moveright(sf::Event &event);
    
    void heal_small(sf::Event &event);
    void heal_big(sf::Event &event);
    
    //Information for the Fights
    std::map<std::string, int> inventory;
    Backpack_Pokemon* backpack_pokemons[3];
    
    
    sf::Text text;
    sf::Text n_item;
    sf::Text money_account;
    sf::Sprite background_screen;
    sf::Sprite backpack_graph;
    sf::Sprite rectangle;
    sf::Sprite money;
    
    //Sprites for Pokemon Display
      
    //Slots
    sf::Sprite empty_slot;
    sf::Sprite not_selected_slot;
    sf::Sprite selected_slot;
      
    //Pokeballs
    sf::Sprite poke_close;
    sf::Sprite poke_open;
      
    //Pokemon Names
    sf::Text poke_name;
      
    //Pokemon Levels
    sf::Text level;
      
    //Type
    sf::Sprite earth;
    sf::Sprite water;
    sf::Sprite air;
    sf::Sprite fire;
    
    int num_item();
    int getPresseditem();
    int Selecteditem;
    int Selecteditem_pokemon;
    int number; //contains the actual number of items
    int wallet;
    int actual_column;
    float health_poke;
    
    string location;
    
private:
    void draw_background(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    void draw_menu(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    void draw_pokemon(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    
    
    int capacity;
    
    
    sf::Texture texture_background;
    sf::Texture texture_backpack;
    sf::Texture rectangle_texture;
    sf::Texture money_texture;
    sf::Texture slots;
    sf::Texture types;
    sf::Font font;
    sf::Font font_menu;
    sf::Text menu[6];
    sf::Text quantity[6];
    sf::Text instruction;
    
    float width_backpack;
    float width_title;
    float width_i;
    bool arrow;
    bool release;
    bool release_left;
    bool release_right;
    bool release_small_health;
    bool release_big_health;
    
    //booleans for potion
    bool small_selected;
    bool big_selected;
    
    sf::FloatRect getViewBounds(const sf::View &view);
    
    void switchPokemon(sf::RenderWindow &window, sf::Event &event, sf::View &view, Trainer &trainer);
    bool sw;
    int swi1;
    int swi2;
};

//dictionnary giving the different possible existing items in the game
const std::string item_type[] = {
    "Normalball","Superball", "Masterball", "SmallHealthPotion", "BigHealthPotion", "Torch"
};

//Function to create strings from values
template <typename T>
std::string toString(T arg){
    std::stringstream ss; 
    ss << arg;
    return ss.str();
}

