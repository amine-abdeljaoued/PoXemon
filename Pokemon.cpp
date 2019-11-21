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
		if (!pic.loadFromFile("eevee.png")) std::cout << "could not load" << std::endl;
		pic.loadFromFile("eevee.png");
		sprite.setTexture(pic);
		sprite.setScale(sf::Vector2f(0.4f, 0.4f));
	}

	void Pokemon::update(float& deltaTime, sf::RenderWindow& window) {   // Movement is dependant on time not on frame rate
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

		//bullets---------------------------

		//we should not be able to shoot continuously
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Bullet new_bullet;
			//we want the bullet to start from the midlle right of the pokemon
			//for later: careful if we change the origin of the pokemon
			float x_bullet = x + sprite.getGlobalBounds().width;
			float y_bullet = y + sprite.getGlobalBounds().height / 2;
			sf::Vector2f initial_pos(x_bullet, y_bullet);
			new_bullet.setPosition(initial_pos); // start at the 'middle-right' of the pokemon

			//Get the mouse position:
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			//sf::Mouse::getPosition returns the position of the curson in window coordinates 
			//while all the entities use world coordinates.
			//We fix this by using the mapPixelToCoords member function.
			sf::Vector2f mouse_position = window.mapPixelToCoords(mouse);
			new_bullet.set_shoot_dir( mouse_position, initial_pos);

			bullets.push_back(new_bullet);//append the new bullet to our array
		}
		//-----------------------------------

		 ball.update(deltaTime);
		 
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



	void Pokemon::update_bullets(float& deltaTime) {
		for (int  i = 0; i < bullets.size(); i++) {
			bullets[i].update(deltaTime);
			if (bullets[i].offscreen())
				bullets.erase(bullets.begin() + i);
			//we loop over the bullets and if a bullet is offscreen, remove it
			//we will also need to chack collisions
			// I think the 'erase()' this is pretty inefficient, we might need to find a better way
		}
	}
