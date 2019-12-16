#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Backpack_content.h"

class Background {
public:
    Background(float width, float height, Backpack backpack);
    
    Backpack backpack;
    
    sf::Sprite background;
    sf::Sprite backpack_graph;
    
    sf::Texture texture_background;
    sf::Texture texture_backpack;
    
    sf::Text text;
    sf::Text n_item;
    
    sf::Font font;
    
    float width_backpack;
    float width_title;
    float width_i;
};
