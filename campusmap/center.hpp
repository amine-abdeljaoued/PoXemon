#pragma once
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "trainer.hpp"

using namespace std;

class Center {
    public:
        Center();
        void draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer);
    
    private:
        bool arrow;
        sf::FloatRect getViewBounds(const sf::View &view);
        int Selecteditem;
        sf::Font font;
        sf::Text text;
        vector<string> action_list;
        sf::Text action[2];
        
        void Moveup(sf::Event &event);
        void Movedown(sf::Event &event);
};
