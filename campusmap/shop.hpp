#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "trainer.hpp"
#include "Backpack_map.hpp"
#pragma once

using namespace std;

class Shop
{
    public:
        Shop();
        vector<string> item_list;
        map<string,int> price;
        void Buy(sf::Event &event, Trainer &trainer, BackpackMap &backpack);
        void Moveup(sf::Event &event);
        void Movedown(sf::Event &event);
        void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);
        sf::Sprite moneyI;
        sf::Sprite button;
        
    private:
        sf::Font font;
        sf::Text item[5];
        sf::Text price_column[5];
        sf::FloatRect getViewBounds(const sf::View &view);
        int Selecteditem;
        void draw_shop(sf::RenderWindow &window, sf::View &view, sf::Event &event);
        void draw_money(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack);
        sf::Texture money_texture;
        sf::Texture button_texture;
        bool arrow;
        bool release;
};










