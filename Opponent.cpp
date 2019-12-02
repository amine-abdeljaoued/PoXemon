#include "Opponent.h"
#include <iostream>
#include <random>

void Opponent::draw(sf::RenderTarget& target) {
	target.draw(sprite);
	health.draw(target);
	bullets.draw(target);
}

void Opponent::update(float& deltaTime, sf::RenderWindow& window, sf::Clock& clock, sf::Time& elapsed){
	// movement
	velocityX = 0.0f;
	int randomDirection[2]={-1,1};
	int randomIndex=rand() % 2;
	velocityX = randomDirection[randomIndex]*speed;
	velocityY += 981.0f * deltaTime;

	move(deltaTime);

	// shooting
	float& vp = (*player).velocityY;
	float& xp = (*player).x;
	float& yp = (*player).y;
	float time = (x-xp)/2000.f; // note: this is the max speed defined in bullets
	float delta = vp + 981.0f*time;

	bullets.new_shot_opp(x, y, sprite.getGlobalBounds(), window, xp, yp);
	bullets.update(deltaTime, clock, elapsed);

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

