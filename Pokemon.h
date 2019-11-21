#pragma once
#include "Bullet.h"
#include "Pokeball.h"
#include <SFML/Graphics.hpp>



class Pokemon {
public:
	sf::Sprite sprite;
	float x;                //x and y store current position
	float y;
	float speed;            //Determines how far pokemon moves each time you press l/r
	float velocityX;
	float velocityY;    //will be needed to jump
	float accY;
	Pokeball ball;
	float jumpHeight;       //how high this pokemon can jump
	bool canJump;           //If you're on the ground, you can jump
	bool shooting;          //If you're shooting, we want to draw the pokeball


	//-----------
	Bullet bullet; //the bullet might depend on the pokemon
	//ex : the sprite could vary depending on the pokemon type, the damages can be different...
	bool shooting_bullet;
	std::vector<Bullet> bullets;
	void update_bullets(float& deltaTime);
	//-----------


	Pokemon(float xstart, float ystart, float h, float v);
	void update(float& deltaTime, sf::RenderWindow& window);
	void move(float& deltaTime);

	sf::RectangleShape rect;
private:
	sf::Texture pic;
};
