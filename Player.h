#include <iostream>
#include "Pokemon.h"
#pragma once

class Player: public Pokemon {
public:
	Player(float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity, std::string name)
		: Pokemon(xstart, ystart, h, v, hp, path, pokemon_rarity, name) {
		was_left = true;
		sprite.setScale(sf::Vector2f(-0.5f, 0.5f));//it has to face towards the right (intially, the images are all 'facing towards the left')
	};

    void update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, sf::Time& elapsed, float& groundY);
    void move(float& deltaTime);
    void draw(sf::RenderTarget& target);

	bool was_left;//true when the player is at the left of the opponent
	void update_sprite_orientation();//make the pokemons face each other

	void collision_opponent();//to complete
};