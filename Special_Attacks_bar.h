#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream>

//the special_attacks_bar shows our available special attacks + how much time is left for them

class Special_Attacks_Bar {

public:
	int type; // depends on the pokemon's type
	int xpos;
	int ypos;
	int boxsize; // size of the boxes which have a picture of each special attack - they are square

	Special_Attacks_Bar(); // will need to initialise it with the type of the pokemon, and update it as the pokemon's level increases
	void draw(sf::RenderTarget& target);
	void setPosition(float x, float y);     // the components must be moved together
	void update(sf::Time& time1, sf::Time& time2, sf::Time& time3, sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3);
	void initialise();
	void initial_state();

// Specical Attack 1
	bool attack1_available;
	bool shooting1; 		// tells us if we are shooting
	bool regenerating1; 	// tells us if we are regenerating
	int attack1_time;
	int regeneration1_time;
	sf::Sprite key1; 	// Tells the player which key to press
	sf::Texture key1_texture;
    sf::RectangleShape base_rect;
	sf::RectangleShape timer_rect;
	sf::Sprite attack_1_sprite;   // Image of the bullet
	sf::Texture attack_1_texture;       
	sf::Texture attack_1_texture_bw; // picture in black and white, which is used once you've used the special attack

// Special Attack 2
	bool attack2_available;
	bool shooting2; 
	int attack2_time;
	int regeneration2_time;

// Special Attack 3
	bool attack3_available;
	bool shooting3; 
	int attack3_time;
	int regeneration3_time;

// General - relating to levels
    sf::Texture lock;  // shown when we haven't reached a high enough level yet 
};
