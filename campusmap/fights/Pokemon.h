#pragma once
#include "Bullet.h"
#include "Artillery.h"
#include "Pokeball.h"
#include "Health.h"
#include "Backpack_Pokemon.cpp"
#include <SFML/Graphics.hpp>
#include <string>


class Pokemon {
public:
	int index;//index in the backpack
	float rarity;
	int level = 1; 			// must be implemented by pokemon team!!
	std::string name;
	sf::Sprite sprite;
	float groundY; 			// lowest point we can go
	float x;                //x and y store current position
	float y;
	float speed;            //Determines how far pokemon moves each time you press l/r
	float velocityX;
	float velocityY;    	//will be needed to jump
	float accY;
	float jumpHeight;       // how high this pokemon can jump
	bool canJump;           // If you're on the ground, you can jump
	bool shooting;          // If you're shooting, we want to draw the pokeball
	bool special_attack_1;
	Healthbar health;		// Health between 1 and 100
	Artillery bullets; 		// This is where all bullets are stored
							// If we want bullets to depend on Pokemon, bullets must have a constructor
	Pokemon* enemy;

	Pokemon()=default;
	Pokemon(sf::RenderWindow& window, float h, float v, Backpack_Pokemon backpack_pokemon);
	void set_enemy(Pokemon* enemy);

	void death_disappear(float& deltaTime); //scale down and make the pokemon 'implode'
	
	int type; /* We know which type a pokemon is by its identifier type
							10 - earth
							20 - water
							30 - air
							40 - fire
							(use multiples of 10 to avoid confusion with backpack) */
//protected:
	sf::Texture pic;
};
