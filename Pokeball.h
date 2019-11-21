#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


//remarks / stuff to change
/*
We sould be able to throw a pokeball only if we have some in our backpack
We can only throw one pokeball at a time
When we throw one, the game should 'stop', until we know whether or not we caatch the opponent
Normally, the pokeball is not thrown by the pokemon but by the player
*/

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
private:
	sf::Texture pic;
};