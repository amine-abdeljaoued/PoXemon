#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Pokeball {
public:
	float velocityX = 800;  //Set the speed of each of the pokeballs
	float ballHeight = 30;
	float velocityY;
	float x;
	float y;
	sf::Sprite ball;
	float gravity = 981.0f / 2;   //This will make the parabolic trajectory

	Pokeball();

	void dissapear();

	void setPosition(float& xpos, float& ypos);
	bool update(float deltaTime);
};