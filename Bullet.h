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
	float max_speed = 1000.0;
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
	bool offscreen();
	virtual void deletion();
	void reflect_ground(float& groundY);

	sf::Texture bpic;
};

// ---------------------------------------------------------------------------------------------------
// SPECIAL ATTACK 1

/* 	The following are variables needed to access the sprite sheets for the different types 
	They of the form an array of floats with the following characteristics
	0-6: flying sprite sheet
	7-12: collision sprite sheet
	array = [0: xstart position in sprite sheet, 1: ystart position in sprite sheet, 2: size of square,
			3: number of times you can shift right, 4: number of times you can shift down, 
			5: number of times you can shift right in the last row, 6: scale it should be set at 
			next 7 are the same as above for the explode sheet] 
	values are given as the value you can travel to 
	e.g. if you can move 8 times, the value is 7 because you can access 0 --> 7 (8 shifts) */

const float earth [14] = {0, 0, 256, 7, 7, 7, 0.17,
						  0, 0, 192, 4, 1, 1, 0.4 }; // type 10
/* const float air [14] ; // type 30
const float water [14] ; // type 20
const float fire [14] ; // type 40
 */

class Bullet_Attack1: public Bullet{
public:
	int i; 	// This keeps track of for how many frames our image has shown
				// We only want to change image every two frames (otherwise too fast)
    Bullet_Attack1(int ptype): Bullet() {
		type = ptype;	// the type of bullets we attack with is the 'class'/type of the pokemon
		posx = 0;
		posy = 0;
		i = 1;

		// initialise our array of useful constants to the above ones
		if(type == 10){	for (int i=0; i<14; i++) {array[i] = earth[i];} }
		if(type == 20){/*to be done*/};
		if(type == 30){/*to be done*/;};
		if(type == 40){/*to be done*/};

		//initialise image
		if (!bpic.loadFromFile("Images/rocks1.png")) std::cout << "could not load attack 1 image" << std::endl; 
		bpic.loadFromFile("Images/rocks1.png");
		if (!deleting_pic.loadFromFile("Images/rock_explode.png")) std::cout << "could not load attack 1 explode image" << std::endl; 
		deleting_pic.loadFromFile("Images/rock_explode.png");

		bullet.setTexture(bpic);
		bullet.setTextureRect(sf::IntRect(array[0]*array[2],array[0]*array[2],array[2],array[2])); 	// This chooses which part of the sprite we use - first two arguments are where you start
																					// second 2 args are the size
		bullet.setScale(sf::Vector2f(array[6], array[6]));
		bullet.setOrigin(sf::Vector2f(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2));	
	};

	void update_image();
	virtual bool update(float& deltaTime, float& groundY);
	virtual void deletion();

private:
	sf::Texture deleting_pic;
	int type;
	float array[14];
	int posx; // (posx, posy) is our block position in the sprite sheet
	int posy;
};