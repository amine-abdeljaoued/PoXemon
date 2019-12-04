#include "Opponent.h"
#include <iostream>
#include <random>

void Opponent::draw(sf::RenderTarget& target) {
	target.draw(sprite);
	health.draw(target);
	bullets.draw(target);
	//unhandled exception here !
}

void Opponent::update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, sf::Time& elapsed, float& groundY){
	//Movement
    	velocityX = 0.0f;
		velocityX = direction * speed;

		//random left-right movement
		//We choose a random amount of time (time_change_dir) throughout which we dont change direction.
		//once it has elapsed, we change direction and repeat the process.
		elapsed_direction = this->clock.getElapsedTime();
		if (elapsed_direction.asSeconds() > time_change_dir) {
			time_change_dir = 0.3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 0.3)));
			this->clock.restart();
			direction *= -1;
		}

		//random jumps
		if (rand() < 0.002 * ((double)RAND_MAX + 1.0) && canJump) { // probability of jumping of 0.002 at each update (if we are not already jumping)
			canJump = false;       
			velocityY = -sqrt(2.0f * 981.0f * jumpHeight);
		}

		//if it gets too close from the window bounds
		if (sprite.getPosition().x + sprite.getGlobalBounds().width + 20 >= window.getSize().x) {
			direction = -1;
		}
		if ((sprite.getPosition().x - 20 <= 0)) {
			direction = 1;
		}
		
		velocityY += 981.0f * deltaTime;
		move(deltaTime);

	// shooting
		float& vp = (*enemy).velocityY;
		float& xp = (*enemy).x;
		float& yp = (*enemy).y;
	    float time = (x-xp)/2000.f; // note: this is the max speed defined in bullets
		float delta = vp + 981.0f*time;

		bullets.new_shot_opp(x, y, sprite.getGlobalBounds(), window, xp, yp);
		int i = bullets.update(deltaTime, clock, elapsed, (*enemy).sprite, groundY);
		if (i != 0) {
			(*enemy).health.decrease(i);
			//std::cout<<(*enemy).health.health << std::endl;
		}

	// health
		health.update();
}

void Opponent::move(float& deltaTime) {

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

//we randomly choose a number of seconds till we change direction
//until we have not reached this, we keep moving at constant velocity towards this direction
