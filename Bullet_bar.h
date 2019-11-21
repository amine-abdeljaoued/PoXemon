#pragma once
#include <SFML/Graphics.hpp>

class Bullet_bar
{
public:
	Bullet_bar(int max_available_bullets);
	int max_available_bullets ;
	int available_bullets ;
	sf::RectangleShape rectangle;//will probably be changed for a sprite
	//this is basically the bar that has the length of 'full amunition'
	sf::RectangleShape rectangle_amount;
	//this shows the amount of amunition we still have

	void update(int available);
	void draw();
};

