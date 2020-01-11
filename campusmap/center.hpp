#pragma once
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "trainer.hpp"
#include "Backpack_map.hpp"

using namespace std;

class Center {
    public:
        Center();
        void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);
    
        int Selecteditem;
       
        //Switching
        bool sw;
        int swi1;
        int swi2;
    
        //to Switch main menu, switchingPokemon menu
        int counter;
        vector<vector<string>> interface;
    
    private:
        bool arrow;
        sf::FloatRect getViewBounds(const sf::View &view);
        
        sf::Font font;
        
        //Different possible actions
        vector<string> action_list;
        vector<string> pokemon_bag;
        
        void Moveup(sf::Event &event);
        void Movedown(sf::Event &event);
        void heal_pokemons(BackpackMap &backpack, sf::Event &event, Trainer &trainer);
        void switchMenu(sf::RenderWindow &window, BackpackMap &backpack, sf::Event &event, sf::View &view, Trainer &trainer);
        void switchPokemon(sf::RenderWindow &window, BackpackMap &backpack, sf::Event &event, sf::View &view, Trainer &trainer);
};
