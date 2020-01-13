#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>
#include "trainer.hpp"
#include "fights/Backpack_Pokemon.cpp"
#include "Backpack_map.hpp"

using namespace std;

class Box {
    public:
        Box();
        
        vector<string> poke_list;
        Backpack_Pokemon* box_pokemons[10];
    
    //if (box_pokemons[i]) {
    //}
    
        void draw_background(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);
    
        void draw_pokemon(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);
    
        void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);
    
        void Moveup_left(sf::Event &event);
        void Movedown_left(sf::Event &event, BackpackMap &backpack);
        
        void Moveup_right(sf::Event &event);
        void Movedown_right(sf::Event &event);
        
        void Moveleft(sf::Event &event);
        void Moveright(sf::Event &event);
    
        void switchPoke(BackpackMap &backpack, sf::Event &event);
    
        sf::Sprite background_screen;
    
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
    
        int selectedPokemon_right;
        int selectedPokemon_left;
        int actual_column;
        float health_poke;
    
        int width_title;
    
        sf::FloatRect getViewBounds(const sf::View &view);
    
        //Values for switching pokemons
        int column;
        bool sw;
        int swi1;
        int swi2;
        int selectedPokemon_1;
        int selectedPokemon_2;
    
        bool addPokemon(Backpack_Pokemon poke, BackpackMap &backpack);
        
    private:
        sf::Texture background;
        sf::Texture slots;
        sf::Texture types;
        sf::Font font;
        sf::Text instruction;
        sf::Text text;
        
        bool release;
        bool release_left;
        bool release_right;
        bool release_down_left;
        bool release_up_left;
        bool release_down_right;
        bool release_up_right;
    
        bool pointerEmpty(int i);
        bool addPokemonB(std::string name, int level, int index, int health, int type);
};
