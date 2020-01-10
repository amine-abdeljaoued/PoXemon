#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Bullet 
{
public:
	float x = 0;
	float y = 0;
	float max_speed = 850.0;
	bool deleted;
	bool deleting; // To know if is has hit the opponent - then we do the 'exploding' animation (used later)

	sf::Vector2f position;
	sf::Vector2f shoot_dir;
	sf::Sprite bullet;

	Bullet();

	//void setPosition(float& xpos, float& ypos);
	void setPosition(sf::Vector2f& pos);
	void set_shoot_dir(const sf::Vector2f& mouse_position, const sf::Vector2f& initial_position);
	virtual bool update(float& deltaTime, float& groundY);
	bool offscreen(sf::RenderWindow & window);
	virtual void deletion();
	void reflect_ground(float& groundY);

	sf::Texture bpic;
};

// ---------------------------------------------------------------------------------------------------
// SPECIAL ATTACK 1

/* 	The following are variables needed to access the sprite sheets for the different types 
	They of the form an array of floats with the following characteristics
	0-7: flying sprite sheet
	8-15: collision sprite sheet
	array = [0: xstart position in sprite sheet, 1: ystart position in sprite sheet, 2: width of square,
			3: height of square, 4: number of times you can shift right, 5: number of times you can shift down, 
			6: number of times you can shift right in the last row, 7: scale it should be set at 
			next 7 are the same as above for the explode sheet] 
	values are given as the value you can travel to 
	e.g. if you can move 8 times, the value is 7 because you can access 0 --> 7 (8 shifts) */

const float earth [16] = {0, 0, 256, 256, 7, 7, 7, 0.17,
						  0, 0, 192, 192,  4, 1, 1, 0.4 }; 	// type 10
const float water [16] = {0, 0, 131.33, 119.5, 4, 0, 4, 0.3,
						  5, 0, 131.33, 119.5, 5, 1, 2, 0.3}; // type 20
const float air [16] = {0, 0, 182, 206, 3, 1, 3, 0.35,
						0, 2, 182, 206, 3, 2, 2, 0.35};		// type 30
const float fire [16] = {0, 0, 128, 128, 3, 0, 3, 0.5,
						 0, 1, 256, 256, 0, 5, 0, 0.2 };  	// type 40

class Bullet_Attack1: public Bullet{
public:
	int i; 	// This keeps track of for how many frames our image has shown
				// We only want to change image every two frames (otherwise too fast)

    Bullet_Attack1(int ptype): Bullet() {
		type = ptype;	// the type of bullets we attack with is the 'class'/type of the pokemon
		posx = 0;
		posy = 0;
		i = 1;

		// initialise our array of useful constants to the above ones and the texture
		if(type == 10){	
			for (int i=0; i<16; i++) {array[i] = earth[i];} 
			if (!bpic.loadFromFile("fights/Images/rocks1.png")) std::cout << "could not load attack 1 earth image" << std::endl; 
			bpic.loadFromFile("fights/Images/rocks1.png");
			if (!deleting_pic.loadFromFile("fights/Images/rock_explode.png")) std::cout << "could not load attack 1 earth explode image" << std::endl; 
			deleting_pic.loadFromFile("fights/Images/rock_explode.png");}
		if(type == 20){	
			for (int i=0; i<16; i++) {array[i] = water[i];} 
			if (!bpic.loadFromFile("fights/Images/water.png")) std::cout << "could not load attack 1 water image" << std::endl; 
			bpic.loadFromFile("fights/Images/water.png");
			if (!deleting_pic.loadFromFile("fights/Images/water.png")) std::cout << "could not load attack 1 water explode image" << std::endl; 
			deleting_pic.loadFromFile("fights/Images/water.png");}
		if(type == 30){	
			for (int i=0; i<16; i++) {array[i] = air[i];} 
			if (!bpic.loadFromFile("fights/Images/iceball.png")) std::cout << "could not load attack 1 ice image" << std::endl; 
			bpic.loadFromFile("fights/Images/iceball.png");
			if (!deleting_pic.loadFromFile("fights/Images/iceball.png")) std::cout << "could not load attack 1 ice explode image" << std::endl; 
			deleting_pic.loadFromFile("fights/Images/iceball.png");}
		if(type == 40){
			for (int i=0; i<16; i++) {array[i] = fire[i];} 
			if (!bpic.loadFromFile("fights/Images/fireball.png")) std::cout << "could not load attack 1 fire image" << std::endl; 
			bpic.loadFromFile("fights/Images/fireball.png");
			if (!deleting_pic.loadFromFile("fights/Images/fireball_explode.png")) std::cout << "could not load attack 1 fire explode image" << std::endl; 
			deleting_pic.loadFromFile("fights/Images/fireball_explode.png");};

		//initialise image
		bullet.setTexture(bpic);
		bullet.setTextureRect(sf::IntRect(array[0]*array[2],array[0]*array[3],array[2],array[3])); 	// This chooses which part of the sprite we use - first two arguments are where you start
																					// second 2 args are the size
		bullet.setScale(sf::Vector2f(array[7], array[7]));
		bullet.setOrigin(sf::Vector2f(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2));	
	};

	void update_image();
	virtual bool update(float& deltaTime, float& groundY);
	virtual void deletion();

private:
	sf::Texture deleting_pic;
	int type;
	float array[16];
	int posx; // (posx, posy) is our block position in the sprite sheet
	int posy;
};