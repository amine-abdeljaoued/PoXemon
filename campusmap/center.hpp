#pragma once
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "trainer.hpp"
#include "Backpack_map.hpp"
#include "box.hpp"

using namespace std;

class Center {
    public:
        Center();
        void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);

        int Selecteditem;
    
    private:
        bool arrow;
        sf::FloatRect getViewBounds(const sf::View &view);
        
        sf::Font font;
        
        //Different possible actions
        vector<string> action_list;
        
        void Moveup(sf::Event &event);
        void Movedown(sf::Event &event);
        void heal_pokemons(BackpackMap &backpack, sf::Event &event, Trainer &trainer):
};
