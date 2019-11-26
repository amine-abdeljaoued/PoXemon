#include "Opponent.h"
#include <iostream>



void Opponent::update(float& deltaTime){
    		velocityX = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			std::cout<<"left"<<std::endl;
			velocityX += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			velocityX -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.canJump) {
			
		}
		

		if (player.shooting) {
			
		}

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

