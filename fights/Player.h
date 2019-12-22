#include <iostream>
#include "Pokemon.h"
#pragma once

class Player: public Pokemon {
public:
	Player(float xstart, float ystart, float h, float v, Backpack_Pokemon backpack_pokemon)
		: Pokemon(xstart, ystart, h, v, backpack_pokemon) {
		was_left = true;
		sprite.setScale(sf::Vector2f(-0.5f, 0.5f));//it has to face towards the right (intially, the images are all 'facing towards the left')
	};
	
    void update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, 
				sf::Time& elapsed, sf::Time& attack1, sf::Time& attack2, sf::Time& attack3, 
				sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3, float& groundY);
    void move(float& deltaTime);
    void draw(sf::RenderWindow& target);
	void draw(sf::RenderWindow& target, sf::Shader* shader);

	bool was_left;//true when the player is at the left of the opponent
	void update_sprite_orientation();//make the pokemons face each other

	void collision_opponent();//to complete
};