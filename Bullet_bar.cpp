#include "Bullet_bar.h"


Bullet_bar::Bullet_bar(int max) {
	max_available_bullets = max;
	available_bullets = max;
	rectangle.setFillColor(sf::Color::White);
	rectangle_amount.setFillColor(sf::Color::Red);
}

void Bullet_bar::update(int available) {
}

void Bullet_bar::draw(){
}
