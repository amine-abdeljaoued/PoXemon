#pragma once
#include <SFML/Graphics.hpp>
#include <string> //this will be used in the cpp 
#include <iostream>

//the bullet_bar shows our pokemon bullet and how many bullets we have remaining 

class BulletBar {

public:
	BulletBar();
	void draw(sf::RenderTarget& target);
	void setPosition(float x, float y);     // the two components of the health bar must be moved together
	int available_bullets; // maybe its not very good to have it both here and in artillery

	int xpos;
	int ypos;

//private:
	sf::Sprite bullet_sprite;    
	sf::Texture bullet_pic;
	sf::Texture bullet_pic_bw; //picture in black and white, which is used for the 'empty' part
	void update(int additional_bullet); //additional_bullet = +-1 (if the number of bullets regenerates or if we shoot)
	sf::Font font;
	sf::Text nb_text; //text (made of digits) that corresponds to the available bullets

	//useless for the moment----------------------
	float empty_part; //we use this to display in color the 'proportion' of available bullets
	                  //the rest will be the same image but in black and white
	sf::IntRect empty_rec;


};
