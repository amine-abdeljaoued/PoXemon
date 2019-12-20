#pragma once
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "trainer.hpp"

using namespace std;

class Shop
{
    public:
        Shop();
        vector<string> item_list;
        map<string,int> price;
        void Moveup(sf::Event &event);
        void Movedown(sf::Event &event);
        void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
        sf::Sprite moneyI;
        sf::Sprite button;
        
    
    private:
        sf::Font font;
        sf::Text item[7];
        sf::FloatRect getViewBounds(const sf::View &view);
        int Selecteditem;
        void draw_shop(sf::RenderWindow &window, sf::View &view, sf::Event &event);
        void draw_money(sf::RenderWindow &window, sf::View &view, sf::Event &event);
        int money;
        sf::Texture money_texture;
        sf::Texture button_texture;
};



