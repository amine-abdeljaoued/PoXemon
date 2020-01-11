#include <iostream>
#include "Pokemon.h"
#pragma once

class Player: public Pokemon {
public:
	Player(sf::RenderWindow& window, float h, float v, Backpack_Pokemon backpack_pokemon)
	: Pokemon(window, h, v, backpack_pokemon) {
		sf::Vector2u TextureSize = pic.getSize(); 	//Get size of texture.
		sf::Vector2u WindowSize = window.getSize();      //Get size of window.

		float ScaleY = (float) WindowSize.y / TextureSize.y; //Calculate scale.
		sprite.setScale(-ScaleY/5, ScaleY/5);	//Set scale: it has to face towards the right (intially, the images are all 'facing towards the left')

		was_left = true;
		
		x = window.getSize().x/5;
		y = 3*window.getSize().y/5;
		groundY = y;

		sprite.setPosition(sf::Vector2f(x, y));
		health.setPosition(sprite.getGlobalBounds().width/2, window.getSize().y/20);
	};

    void update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, 
				sf::Time& elapsed, sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3, float& groundY);
    void move(float& deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& target);
	void draw(sf::RenderTexture& texture);

	bool was_left;//true when the player is at the left of the opponent
	void update_sprite_orientation();//make the pokemons face each other

	void collision_opponent();//to complete
};