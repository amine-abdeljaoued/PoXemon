#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//bullets are the default attack
//They follow a straight line
//If they touch a pokemon, we should make them dissapear, and decrease its life


//we may get inspriation from this for the special attacks 

//To fix: we shouldn't be able to shoot continuously (too easy)
//?? one shot per click, or a limited frequency of shots, or a limited number of shoots that regenerates with time

//?? ideas ??
//make bullets bounce on the ground
//make an 'explosion' when they touch the opponent

class Bullet 
{
public:
	float x;
	float y;
	float max_speed = 2000.0;

	sf::Vector2f position;
	sf::Vector2f shoot_dir;
	sf::Sprite bullet;

	Bullet();

	//void setPosition(float& xpos, float& ypos);
	void setPosition(sf::Vector2f& pos);
	void set_shoot_dir(sf::Vector2f mouse_position, sf::Vector2f initial_position);
	bool update(float deltaTime);
	bool offscreen();
	bool collide();
private:
	sf::Texture bpic;
};



