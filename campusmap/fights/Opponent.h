#include <iostream>
#include "Pokemon.h"
#pragma once



class Opponent: public Pokemon{

protected:
    Pokemon* player;
public:

    Opponent(sf::RenderWindow& window, float h, float v, Backpack_Pokemon backpack_pokemon)
    :Pokemon(window, h, v, backpack_pokemon){
		sf::Vector2u TextureSize = pic.getSize(); 	//Get size of texture.
		sf::Vector2u WindowSize = window.getSize();      //Get size of window.

		float ScaleY = (float) WindowSize.y / TextureSize.y; //Calculate scale.
		Scale = ScaleY / 5;
		sprite.setScale(Scale, Scale);	//Set scale

		speed = 400;
		int randomDirection[2] = { -1,1 };
		int randomIndex = rand() % 2;
		direction = randomDirection[randomIndex];
		time_change_dir = 0.3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 0.3))); //random float between 0.3 and 2

		x = 4*window.getSize().x/5;
		y = 3*window.getSize().y/5;
		groundY = y;

		sprite.setPosition(sf::Vector2f(x, y));
		health.setPosition(window.getSize().x - sprite.getGlobalBounds().width/2 - health.bar.getGlobalBounds().width, window.getSize().y/20);
    };

    void update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, sf::Time& elapsed, 
				sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3, float& groundY);
    void draw(sf::RenderWindow& target);
	void draw(sf::RenderTexture& texture);
    void move(float& deltaTime);

	int direction;
	float time_change_dir; //time before changing direction (updated each time the bot changes direction)
	sf::Clock clock;
	sf::Time elapsed_direction;
	
};