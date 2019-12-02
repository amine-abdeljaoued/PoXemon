#include <iostream>
#include "Pokemon.h"
#pragma once

class Player: public Pokemon {
public:
    Player(float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity, std::string name)
    : Pokemon(xstart, ystart, h, v, hp, path, pokemon_rarity, name){};

    void update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, sf::Time& elapsed, const sf::Sprite& opponent_sprite, float& groundY);
    void move(float& deltaTime);
    void draw(sf::RenderTarget& target);
};