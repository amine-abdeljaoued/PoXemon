#include "Opponent.h"
#include <iostream>
#include <random>

void Opponent::draw(sf::RenderWindow& target) {
	target.draw(sprite);
	health.draw(target);
	bullets.draw(target);
	//unhandeled exception here !
}

void Opponent::draw(sf::RenderTexture& texture){
	texture.draw(sprite);
	health.draw(texture);
	bullets.draw(texture);
}

void Opponent::update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, sf::Time& elapsed, 
						sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3, float& groundY){
	//Movement
	velocityX = 0.0f;
	velocityX = direction * speed;

	//random left-right movement
	//We choose a random amount of time (time_change_dir) throughout which we dont change direction.
	//once it has elapsed, we change direction and repeat the process.
	/*elapsed_direction = this->clock.getElapsedTime();
	if (elapsed_direction.asSeconds() > time_change_dir) {
		time_change_dir = 0.3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 0.3)));
		this->clock.restart();
		direction *= -1;
	}*/

	////jumps to avoid bullets 
	//if (!(enemy->bullets.bullets.empty())) {
	//	//get the position of the bullet that was shot first (that is still on screen and hasn't collided with the opponent)
	//	float bx = (enemy->bullets.bullets[0])->position.x;
	//	float by = (enemy->bullets.bullets[0])->position.y;
	//	if (abs(x - bx) <= 200 && abs(y-by)<=30){//check if the bullet is close 
	//		if (canJump) {
	//			//to do: find a way not to make it always jump (otherwise its too hard to win)
	//			std::cout << "esquive !" << std::endl;
	//			canJump = false;
	//			velocityY = -sqrt(2.0f * 981.0f * jumpHeight);//jump
	//		}
	//	}
	//}

	//random jumps
	if (rand() < 0.0005 * ((double)RAND_MAX + 1.0) && canJump) { // probability of jumping of 0.0005 at each update (if we are not already jumping)
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
	int i = bullets.update(window, deltaTime, clock, elapsed, clock1, clock2, clock3, (*enemy).sprite, groundY);
	if (i != 0) {
		(*enemy).health.decrease(i);
	}
	// health
	health.update();
}

void Opponent::move(float& deltaTime) {

	x += velocityX * deltaTime;
	y += velocityY * deltaTime;
	if (y >= groundY) {
		y = groundY;
		velocityY = 0.0f;
		canJump = true;
	}

	sprite.setPosition(x, y);
}

//we randomly choose a number of seconds till we change direction
//until we have not reached this, we keep moving at constant velocity towards this direction
