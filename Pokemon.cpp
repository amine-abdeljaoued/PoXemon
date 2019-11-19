#include "Pokemon.h"


	Pokemon::Pokemon(float xstart, float ystart, float h, float v)
	{
		velocityX = 0.0f;
		velocityY = 0.0f;
		jumpHeight = h;
		speed = v;
		canJump = true;
		shooting = false;
		x = xstart;
		y = ystart;
		sprite.setPosition(sf::Vector2f(x, y));
		sf::Texture pic;
		pic.loadFromFile("eevee.png");
		sprite.setTexture(pic);
		sprite.setScale(sf::Vector2f(0.4f, 0.4f));
	}

	void Pokemon::update(float& deltaTime) {   // Movement is dependant on time not on frame rate
									// This means that we can have smooth movement over multiple frames, instead of static movement per each frame
		velocityX = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			velocityX -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			velocityX += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump) {
			canJump = false;       //While jumping you can't jump
			velocityY = -sqrt(2.0f * 981.0f * jumpHeight);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			ball.setPosition(x, y);     // Need to figure out where the starting x and y position are
			ball.velocityY = -sqrt(2.0f * 981.0f * ball.ballHeight); //We need to reset the ball's position and starting speed when you shoot, that's why its in this class
			shooting = true;
		}

		if (shooting) {
			bool shoot = ball.update(deltaTime);
			if (!shoot) { shooting = false; }
		}

		velocityY += 981.0f * deltaTime;
		move(deltaTime);
	}



	void Pokemon::move(float& deltaTime) {
		x += velocityX * deltaTime;
		y += velocityY * deltaTime;
		float groundY = 300.0f; //Cannot go below this height
		if (y >= groundY) {
			y = groundY;
			velocityY = 0.0f;
			canJump = true;
		}

		sprite.setPosition(x, y);
	}
