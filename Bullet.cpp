
#include "Bullet.h"


Bullet::Bullet() {

	sf::Texture pic;
	pic.loadFromFile("pokeball.png");//to change
	bullet.setTexture(pic);
	//I find easier to set the origin at center
	bullet.setOrigin(sf::Vector2f(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2));
	bullet.setScale(sf::Vector2f(0.2f, 0.2f));
}


void Bullet::setPosition(sf::Vector2f& pos) {
	//x = xpos;
	//y = ypos;
	position = pos;
	bullet.setPosition(position);
}


void Bullet::set_shoot_dir(sf::Vector2f mouse_position, sf::Vector2f initial_pos) {
	//float x and float y stand for the initial position
	shoot_dir = mouse_position - initial_pos;
	//now we normalize this vector
	float norm = sqrt(pow(shoot_dir.x, 2) + pow(shoot_dir.y, 2));
	shoot_dir = shoot_dir / norm;
}

bool Bullet::update(float deltaTime) {
	
	//x += shoot_dir.x * deltaTime *max_speed;
	//y += shoot_dir.y * deltaTime *max_speed;

	position += shoot_dir *deltaTime* max_speed;
	setPosition(position);
	return true;
}

bool Bullet::offscreen() {
	float groundX = 1400.f;
	if (x >= groundX) return true;
	return false;
}

