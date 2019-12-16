#include "Background.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Backpack_content.h"

template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

Background::Background(float width, float height, Backpack backpack) {
    
    if (!texture_background.loadFromFile(resourcePath() + "screen_menu.jpg")) {
        std::cout<<"error"<<std::endl;
    }
    if (!texture_backpack.loadFromFile(resourcePath() + "Pt_bag.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        std::cout<<"error"<<std::endl;
    }
    
    //Set Scale of Background image
    background.setTexture(texture_background);
    background.setScale(7, 7);
    
    //Set backpack texture
    backpack_graph.setTexture(texture_backpack);
    
    //Position backpack on window
    width_backpack = backpack_graph.getGlobalBounds().width;
    backpack_graph.setOrigin(sf::Vector2f(width_backpack/2, width_backpack/2));
    backpack_graph.setPosition(sf::Vector2f(width/3.2, height/1.6));
    backpack_graph.setScale(3, 3);
    
    //Set title Color, Position and Font
    text.setString("Backpack");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);
    
    width_title = text.getLocalBounds().width;
    text.setOrigin(sf::Vector2f(width_title/2, 0));
    text.setPosition(width/2, 0);
    
    //Set Display of total number of items
    n_item.setString("Items: " + toString(backpack.num_item()) + "/100");
    n_item.setFont(font);
    n_item.setStyle(50);
    n_item.setFillColor(sf::Color::Black);
    
    width_i = n_item.getLocalBounds().width;
    n_item.setOrigin(sf::Vector2f(width_i/2, 0));
    n_item.setPosition(sf::Vector2f((width/3.2)-(width_i/2)-10, height/1.6));
}
