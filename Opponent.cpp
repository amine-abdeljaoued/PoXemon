#include "Opponent.h"
#include <iostream>
#include <random>

void Opponent::update(float& deltaTime){
    	velocityX = 0.0f;
		int randomDirection[2]={-1,1};
		int randomIndex=rand() % 2;
		velocityX = randomDirection[randomIndex]*speed;


		velocityY += 981.0f * deltaTime;
		
		move(deltaTime);
		
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

